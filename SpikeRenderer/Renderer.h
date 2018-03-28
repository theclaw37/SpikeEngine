#pragma once

#include "SpikeUI.h"

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

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")

#ifdef DLL_SPIKERENDERER
#define SPIKERENDERER_EXPORT __declspec(dllexport)
#else
#define SPIKERENDERER_EXPORT __declspec(dllimport)
#endif

namespace SpikeRenderer
{
	enum RendererState
	{
		Initial = 0,
		Ready = 1
	};
	class SPIKERENDERER_EXPORT Renderer
	{
	public:
#ifdef _WIN32
		virtual void InitRenderer(HWND, UINT, UINT) = 0;
#endif
		virtual void RenderFrame(float, float, float) = 0;
		virtual void RenderUI(SpikeUI::UI::UI &) = 0;
		virtual void PresentToScreen() = 0;
		virtual void ShutdownRenderer() = 0;
		virtual RendererState GetState() const;
		virtual ~Renderer() = 0;
	protected:
		RendererState RendererState;
	};

	inline Renderer::~Renderer() = default;

	inline RendererState Renderer::GetState() const
	{
		return RendererState;
	}
}
#endif