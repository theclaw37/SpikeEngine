#include "DirectXRenderer.h"
#include "SpikeUtils.h"

SpikeRenderer::DirectX::DirectXRenderer::DirectXRenderer()
{
	RendererState = RendererState::Initial;
}

void SpikeRenderer::DirectX::DirectXRenderer::InitRenderer(HWND hwnd, UINT width, UINT height)
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
		&_DXSwapChain.SwapChain,
		&_DXDevice.Device,
		NULL,
		&_DXDeviceContext.Device);

	ID3D11Texture2D *pBackBuffer;
	_DXSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	_DXDevice->CreateRenderTargetView(pBackBuffer, NULL, &_DXBackBuffer.Device);
	pBackBuffer->Release();

	_DXDeviceContext->OMSetRenderTargets(1, &_DXBackBuffer.Device, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<FLOAT>(width);
	viewport.Height = static_cast<FLOAT>(height);

	_DXDeviceContext->RSSetViewports(1, &viewport);

	// Direct2D stuff
	_DXSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	ID2D1Factory* d2dfactory;
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
		&_DXUIBackBuffer.RenderTarget
	);

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(_DXUIWriteFactory.WriteFactory), (IUnknown**)(&_DXUIWriteFactory.WriteFactory));

	_DXSwapChain->SetFullscreenState(TRUE, NULL);

	RendererState = RendererState::Ready;

	d2dfactory->Release();
}

void SpikeRenderer::DirectX::DirectXRenderer::RenderFrame(float r, float g, float b)
{
	_DXDeviceContext->ClearRenderTargetView(_DXBackBuffer.Device, D3DXCOLOR(r, g, b, 1.0f));
}

void SpikeRenderer::DirectX::DirectXRenderer::RenderUI(SpikeUI::UI::UI & ui)
{
	_DXUIBackBuffer->BeginDraw();

	ui.IterateBackToFront([this](std::shared_ptr<SpikeUI::UI::Drawable> iter)
	{
		switch (iter->DType)
		{
			case SpikeUI::UI::Label:
			{
				auto item = std::static_pointer_cast<SpikeUI::Controls::Label>(iter);
				RenderUILabel(*item);
				break;
			}
			case SpikeUI::UI::Button:
			{
				auto item = std::static_pointer_cast<SpikeUI::Controls::Button>(iter);
				RenderUIButton(*item);
				break;
			}
			case SpikeUI::UI::Progress:
			{
				auto item = std::static_pointer_cast<SpikeUI::Controls::Progress>(iter);
				RenderUIProgress(*item);
				break;
			}
			case SpikeUI::UI::TextArea:
			{
				auto item = std::static_pointer_cast<SpikeUI::Controls::TextArea>(iter);
				RenderUITextArea(*item);
				break;
			}
		}
	});

	_DXUIBackBuffer->EndDraw();
}

void SpikeRenderer::DirectX::DirectXRenderer::PresentToScreen()
{
	_DXSwapChain->Present(0, 0);
}

void SpikeRenderer::DirectX::DirectXRenderer::ShutdownRenderer()
{
	_DXSwapChain->SetFullscreenState(FALSE, NULL);
}

void SpikeRenderer::DirectX::DirectXRenderer::RenderUILabel(SpikeUI::Controls::Label const & label)
{
	D2D1_RECT_F rect = D2D1::RectF(
		label.Place.TopLeft.x,
		label.Place.TopLeft.y,
		label.Place.BottomRight.x,
		label.Place.BottomRight.y);

	_DXUIBackBuffer->DrawTextW(label.Text.c_str(), label.Text.length(), GetTextFormatFor(label.Font)->TextFormatPointer, &rect, GetBrushFor(label.Colour)->BrushPointer, D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

void SpikeRenderer::DirectX::DirectXRenderer::RenderUIButton(SpikeUI::Controls::Button const & button)
{
	D2D1_RECT_F rect = D2D1::RectF(
		button.Place.TopLeft.x,
		button.Place.TopLeft.y,
		button.Place.BottomRight.x,
		button.Place.BottomRight.y);

	_DXUIBackBuffer->FillRectangle(rect, GetBrushFor(button.Colour)->BrushPointer);
}

void SpikeRenderer::DirectX::DirectXRenderer::RenderUIProgress(SpikeUI::Controls::Progress const & progress)
{
	D2D1_RECT_F fill = D2D1::RectF(
		progress.Place.TopLeft.x,
		progress.Place.TopLeft.y,
		progress.GetValueCoord(),
		progress.Place.BottomRight.y);

	D2D1_RECT_F empty = D2D1::RectF(
		progress.GetValueCoord(),
		progress.Place.TopLeft.y,
		progress.Place.BottomRight.x,
		progress.Place.BottomRight.y);

	_DXUIBackBuffer->FillRectangle(fill, GetBrushFor(progress.FillColour)->BrushPointer);
	_DXUIBackBuffer->FillRectangle(empty, GetBrushFor(progress.EmptyColour)->BrushPointer);
}

void SpikeRenderer::DirectX::DirectXRenderer::RenderUITextArea(SpikeUI::Controls::TextArea const & textArea)
{
	D2D1_RECT_F rect = D2D1::RectF(
		textArea.Place.TopLeft.x,
		textArea.Place.TopLeft.y,
		textArea.Place.BottomRight.x,
		textArea.Place.BottomRight.y);

	_DXUIBackBuffer->FillRectangle(rect, GetBrushFor(textArea.BackgroundColour)->BrushPointer);
	_DXUIBackBuffer->DrawTextW(textArea.Text.c_str(), textArea.Text.length(), GetTextFormatFor(textArea.Font)->TextFormatPointer, &rect, GetBrushFor(textArea.TextColour)->BrushPointer, D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

std::shared_ptr<SpikeRenderer::DirectX::Brush> SpikeRenderer::DirectX::DirectXRenderer::GetBrushFor(std::shared_ptr<SpikeUI::Colour> colour)
{
	auto brush = SpikeUtils::ResourceMapping<SpikeUI::Colour, Brush>::RetrieveResource(colour);
	if (!brush)
	{
		ID2D1SolidColorBrush* tempBrush;
		_DXUIBackBuffer->CreateSolidColorBrush(
			D2D1::ColorF(colour->r, colour->g, colour->b),
			&tempBrush);
		return SpikeUtils::ResourceMapping<SpikeUI::Colour, Brush>::RegisterResource(
			colour,
			SpikeUtils::ResourceManager::RegisterResource<Brush>(tempBrush));
	}
	else
		return brush;
}

std::shared_ptr<SpikeRenderer::DirectX::TextFormat> SpikeRenderer::DirectX::DirectXRenderer::GetTextFormatFor(std::shared_ptr<SpikeUI::Containers::Font> font)
{
	auto textFormat = SpikeUtils::ResourceMapping<SpikeUI::Containers::Font, TextFormat>::RetrieveResource(font);
	if (!textFormat)
	{
		IDWriteTextFormat* tempTextFormat;
		_DXUIWriteFactory->CreateTextFormat(
			font->FontFamily.c_str(),
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			font->Size,
			L"",
			&tempTextFormat);
		return SpikeUtils::ResourceMapping<SpikeUI::Containers::Font, TextFormat>::RegisterResource(
			font,
			SpikeUtils::ResourceManager::RegisterResource<TextFormat>(tempTextFormat));
	}
	else
		return textFormat;
}
