#pragma once

namespace SpikeRenderer
{
	class __declspec(dllexport) Renderer
	{
	public:
		virtual void InitRenderer() = 0;
		virtual void RenderFrame() = 0;
		virtual void ShutdownRenderer() = 0;
	};
}
