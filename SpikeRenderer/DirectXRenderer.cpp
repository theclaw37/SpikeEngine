#include "DirectXRenderer.h"
#include "SpikeUtils.h"

SpikeRenderer::DirectXRenderer::DirectXRenderer()
{
	RendererState = RendererState::Initial;
}

void SpikeRenderer::DirectXRenderer::InitRenderer(HWND hwnd, UINT width, UINT height)
{
	Rhwnd = hwnd;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = Rhwnd;
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
	viewport.Width = static_cast<FLOAT>(width);
	viewport.Height = static_cast<FLOAT>(height);

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

	IDXGISurface1* surface;
	pBackBuffer->QueryInterface(__uuidof(IDXGISurface1), (LPVOID*)&surface);

	auto hr = d2dfactory->CreateDxgiSurfaceRenderTarget(
		surface,
		&props,
		&d2dbackbuffer
	);

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), (IUnknown**)(&writeFactory));

	//swapchain->SetFullscreenState(TRUE, NULL);

	RendererState = RendererState::Ready;
}

void SpikeRenderer::DirectXRenderer::RenderFrame(float r, float g, float b)
{
	devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(r, g, b, 1.0f));
}

void SpikeRenderer::DirectXRenderer::RenderUI(SpikeUI::UI::UI & ui)
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(Rhwnd, &cursorPos);
	SpikeUI::Containers::Point point(cursorPos.x, cursorPos.y);

	static bool lButton;
	bool lButtonDown = false, lButtonUp = false;

	if (GetKeyState(VK_LBUTTON) < 0)
	{
		if (!lButton)
		{
			lButtonDown = true;
			lButtonUp = false;
		}
		else
		{
			lButtonDown = false;
			lButtonUp = false;
		}
		lButton = true;
	}
	else
	{
		if (!lButton)
		{
			lButtonDown = false;
			lButtonUp = false;
		}
		else
		{
			lButtonDown = false;
			lButtonUp = true;
		}
		lButton = false;
	}

	ui.UpdateForPointer(point, lButtonDown, lButtonUp);

	d2dbackbuffer->BeginDraw();

	ui.IterateBackToFront([this](std::shared_ptr<SpikeUI::UI::Drawable> iter)
	{
		switch (iter->DType)
		{
			case SpikeUI::UI::DrawableType::Label:
			{
				auto item = std::static_pointer_cast<SpikeUI::Controls::Label>(iter);
				RenderUITextArea(*item);
				break;
			}
			case SpikeUI::UI::DrawableType::Button:
			{
				auto item = std::static_pointer_cast<SpikeUI::Controls::Button>(iter);
				RenderUIButton(*item);
				break;
			}
		}
	});

	d2dbackbuffer->EndDraw();
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

void SpikeRenderer::DirectXRenderer::RenderUITextArea(SpikeUI::Controls::Label const & textArea)
{
	size_t cSize = strlen(textArea.Font.FontFamily.c_str()) + 1;
	wchar_t* wc = new wchar_t[cSize];
	size_t outSize;
	mbstowcs_s(&outSize, wc, cSize, textArea.Font.FontFamily.c_str(), cSize - 1);
	writeFactory->CreateTextFormat(
		wc,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		textArea.Font.Size,
		L"",
		&textFormat);

	delete wc;

	ID2D1SolidColorBrush* brush;
	d2dbackbuffer->CreateSolidColorBrush(
		D2D1::ColorF(textArea.Colour.r, textArea.Colour.g, textArea.Colour.b),
		&brush);

	D2D1_RECT_F rect = D2D1::RectF(
		textArea.Place.TopLeft.x,
		textArea.Place.TopLeft.y,
		textArea.Place.BottomRight.x,
		textArea.Place.BottomRight.y);

	cSize = strlen(textArea.Text.c_str()) + 1;
	wc = new wchar_t[cSize];
	mbstowcs_s(&outSize, wc, cSize, textArea.Text.c_str(), cSize - 1);
	d2dbackbuffer->DrawTextW(wc, wcslen(wc), textFormat, &rect, brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	delete wc;
}

void SpikeRenderer::DirectXRenderer::RenderUIButton(SpikeUI::Controls::Button const & button)
{
	ID2D1SolidColorBrush* brush;
	d2dbackbuffer->CreateSolidColorBrush(
		D2D1::ColorF(button.Colour.r, button.Colour.g, button.Colour.b),
		&brush);

	D2D1_RECT_F rect = D2D1::RectF(
		button.Place.TopLeft.x,
		button.Place.TopLeft.y,
		button.Place.BottomRight.x,
		button.Place.BottomRight.y);

	d2dbackbuffer->FillRectangle(rect, brush);
}
