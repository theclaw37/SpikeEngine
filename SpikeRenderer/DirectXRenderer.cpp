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

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), (IUnknown**)(&writeFactory));

	//swapchain->SetFullscreenState(TRUE, NULL);
}

void SpikeRenderer::DirectXRenderer::RenderFrame(float r, float g, float b)
{
	devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(r, g, b, 1.0f));
}

void SpikeRenderer::DirectXRenderer::RenderUI(SpikeUI::UI::UI ui)
{
	ui.Reset();

	do
	{
		switch (auto elem = ui.GetType())
		{
		case SpikeUI::UI::DrawableType::TextArea:
		{
			auto item = ui.Get<SpikeUI::Text::TextArea>();

			size_t cSize = strlen((*item).Font.FontFamily.c_str()) + 1;
			wchar_t* wc = new wchar_t[cSize];
			size_t outSize;
			mbstowcs_s(&outSize, wc, cSize, (*item).Font.FontFamily.c_str(), cSize - 1);
			writeFactory->CreateTextFormat(
				wc,
				NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				(*item).Font.Size,
				L"",
				&textFormat);

			delete wc;

			d2dbackbuffer->BeginDraw();

			ID2D1SolidColorBrush* brush;
			d2dbackbuffer->CreateSolidColorBrush(
				D2D1::ColorF((*item).Colour.r, (*item).Colour.g, (*item).Colour.b),
				&brush);

			D2D1_RECT_F rect = D2D1::RectF(
				(*item).Place.TopLeft.x,
				(*item).Place.TopLeft.y,
				(*item).Place.BottomRight.x,
				(*item).Place.BottomRight.y);

			cSize = strlen((*item).Text.c_str()) + 1;
			wc = new wchar_t[cSize];
			mbstowcs_s(&outSize, wc, cSize, (*item).Text.c_str(), cSize - 1);
			d2dbackbuffer->DrawTextW(wc, wcslen(wc), textFormat, rect, brush);
			delete wc;

			d2dbackbuffer->EndDraw();
		}break;
		}
	} while (ui.Iterate());
}

void SpikeRenderer::DirectXRenderer::PresentToScreen()
{
	swapchain->Present(0, 0);
}

void SpikeRenderer::DirectXRenderer::ShutdownRenderer()
{
	swapchain->SetFullscreenState(FALSE, NULL);
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}
