#pragma once

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite_1.h>
#include "Renderer.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")

namespace SpikeRenderer
{
	class __declspec(dllexport) DirectXRenderer : public Renderer
	{
	public:
		DirectXRenderer(HWND);
		virtual void InitRenderer();
		virtual void RenderFrame(float, float, float);
		virtual void RenderUI(SpikeUI::UI::UI ui);
		virtual void PresentToScreen();
		virtual void ShutdownRenderer();
	private:
		HWND _hWnd;
		IDXGISwapChain *swapchain;
		ID3D11Device *dev;
		ID3D11DeviceContext *devcon;
		ID3D11RenderTargetView *backbuffer;
		ID2D1Factory* d2dfactory;
		ID2D1RenderTarget* d2dbackbuffer;
		IDWriteTextFormat *textFormat;
		IDWriteFactory1 *writeFactory;
	};
}

#endif