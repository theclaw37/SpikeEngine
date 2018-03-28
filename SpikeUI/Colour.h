#pragma once

#ifdef DLL_SPIKEUI
#define SPIKEUI_EXPORT __declspec(dllexport)
#else
#define SPIKEUI_EXPORT __declspec(dllimport)
#endif

namespace SpikeUI
{
	namespace Colour
	{
		struct SPIKEUI_EXPORT Colour
		{
			double r, g, b;

			Colour(double r, double g, double b) : r(r), g(g), b(b)
			{}
		};
	}
}