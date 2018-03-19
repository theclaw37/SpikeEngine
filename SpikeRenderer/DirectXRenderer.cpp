#include "DirectXRenderer.h"
#include "SpikeConfig.h"
#include "Timer.h"

SpikeRenderer::DirectXRenderer::DirectXRenderer(HWND hWnd) : _hWnd(hWnd)
{
}

void SpikeRenderer::DirectXRenderer::InitRenderer()
{
	SpikeConfig::Config::Instance().Load("config.json");

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = SpikeConfig::Config::Instance().GetWindow().GetClientWidth();
	scd.BufferDesc.Height = SpikeConfig::Config::Instance().GetWindow().GetClientHeight();
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = _hWnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);

	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<FLOAT>(SpikeConfig::Config::Instance().GetWindow().GetClientWidth());
	viewport.Height = static_cast<FLOAT>(SpikeConfig::Config::Instance().GetWindow().GetClientHeight());

	devcon->RSSetViewports(1, &viewport);

	// Direct2D stuff
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dfactory);

	FLOAT dpiX;
	FLOAT dpiY;
	d2dfactory->GetDesktopDpi(&dpiX, &dpiY);

	D2D1_RENDER_TARGET_PROPERTIES props =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpiX,
			dpiY
		);

	IDXGISurface* surface;
	pBackBuffer->QueryInterface(__uuidof(IDXGISurface), (LPVOID*)&surface);


	auto hr = d2dfactory->CreateDxgiSurfaceRenderTarget(
		surface,
		&props,
		&d2dbackbuffer
	);

	IDWriteFactory1 *writeFactory;
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), (IUnknown**)(&writeFactory));

	// create the DRwite text format

	writeFactory->CreateTextFormat(
		L"Times New Roman",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		50,
		L"",
		&textFormat);

	//swapchain->SetFullscreenState(TRUE, NULL);
}

void SpikeRenderer::DirectXRenderer::RenderFrame(float r, float g, float b)
{
	devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(r, g, b, 1.0f));

	D2D1_SIZE_F targetSize = d2dbackbuffer->GetSize();

	d2dbackbuffer->BeginDraw();

	ID2D1SolidColorBrush* brush;
	d2dbackbuffer->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &brush);

	D2D1_RECT_F rect = D2D1::RectF(
		0.0f,
		0.0f,
		100,
		100
	);


	d2dbackbuffer->DrawRectangle(rect, brush);

	const WCHAR *text = L"Hello From Direct2D";
	d2dbackbuffer->DrawTextW(text, wcslen(text), textFormat, D2D1::RectF(0, 0, 800, 600), brush);

    d2dbackbuffer->EndDraw();

	swapchain->Present(0, 0);
}

void SpikeRenderer::DirectXRenderer::RenderUI()
{

}

void SpikeRenderer::DirectXRenderer::ShutdownRenderer()
{
	swapchain->SetFullscreenState(FALSE, NULL);
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}
