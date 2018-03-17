#pragma once

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include "Renderer.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

namespace SpikeRenderer
{
	class __declspec(dllexport) DirectXRenderer : public Renderer
	{
	public:
		DirectXRenderer(HWND);
		virtual void InitRenderer();
		virtual void RenderFrame(float, float, float);
		virtual void ShutdownRenderer();
	private:
		HWND _hWnd;
		IDXGISwapChain *swapchain;
		ID3D11Device *dev;
		ID3D11DeviceContext *devcon;
		ID3D11RenderTargetView *backbuffer;
	};
}

#endif