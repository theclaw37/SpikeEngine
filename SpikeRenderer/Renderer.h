#pragma once

#include "SpikeUI.h"

namespace SpikeRenderer
{
	class __declspec(dllexport) Renderer
	{
	public:
		virtual void InitRenderer(const SpikeUI::UI::UI &) = 0;
		virtual void RenderFrame(float, float, float) = 0;
		virtual void RenderUI() = 0;
		virtual void PresentToScreen() = 0;
		virtual void ShutdownRenderer() = 0;
	};
}
