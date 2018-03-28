#pragma once

#include "Renderer.h"

#ifdef DLL_SPIKERENDERER
#define SPIKERENDERER_EXPORT __declspec(dllexport)
#else
#define SPIKERENDERER_EXPORT __declspec(dllimport)
#endif

namespace SpikeRenderer
{
	class SPIKERENDERER_EXPORT DirectXRenderer : public Renderer
	{
	public:
		DirectXRenderer();
		virtual void InitRenderer(HWND, UINT, UINT);
		virtual void RenderFrame(float, float, float);
		virtual void RenderUI(SpikeUI::UI::UI & ui);
		virtual void PresentToScreen();
		virtual void ShutdownRenderer();
	private:
		HWND Rhwnd;
		IDXGISwapChain *swapchain;
		ID3D11Device *dev;
		ID3D11DeviceContext *devcon;
		ID3D11RenderTargetView *backbuffer;
		ID2D1Factory* d2dfactory;
		ID2D1RenderTarget* d2dbackbuffer;
		IDWriteTextFormat *textFormat;
		IDWriteFactory1 *writeFactory;

		void RenderUITextArea(SpikeUI::Controls::TextArea const & textArea);
		void RenderUIButton(SpikeUI::Controls::Button const & button);
	};
}