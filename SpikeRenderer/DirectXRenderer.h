#pragma once


#ifdef DLL_SPIKERENDERER
#define SPIKERENDERER_EXPORT __declspec(dllexport)
#else
#define SPIKERENDERER_EXPORT __declspec(dllimport)
#endif

#include "Renderer.h"
#include "DXSwapChain.h"
#include "DX3DDevice.h"
#include "DX3DDeviceContext.h"
#include "DX3DRenderTargetView.h"
#include "DX2DRenderTarget.h"
#include "DX2DWriteFactory.h"
#include "Brush.h"
#include "TextFormat.h"

namespace SpikeRenderer
{
	namespace DirectX
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
			DXSwapChain _DXSwapChain;
			DX3DDevice _DXDevice;
			DX3DDeviceContext _DXDeviceContext;
			DX3DRenderTargetView _DXBackBuffer;
			DX2DRenderTarget _DXUIBackBuffer;
			DX2DWriteFactory _DXUIWriteFactory;

			void RenderUILabel(SpikeUI::Controls::Label const &);
			void RenderUIButton(SpikeUI::Controls::Button const &);
			void RenderUIProgress(SpikeUI::Controls::Progress const &);
			void RenderUITextArea(SpikeUI::Controls::TextArea const &);

			std::shared_ptr<Brush> GetBrushFor(std::shared_ptr<SpikeUI::Colour>);
			std::shared_ptr<TextFormat> GetTextFormatFor(std::shared_ptr<SpikeUI::Containers::Font>);
		};
	}
}