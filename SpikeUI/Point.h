#pragma once

#include "Shape.h"

#ifdef DLL_SPIKEUI
#define SPIKEUI_EXPORT __declspec(dllexport)
#else
#define SPIKEUI_EXPORT __declspec(dllimport)
#endif

namespace SpikeUI
{
	namespace Containers
	{
		struct SPIKEUI_EXPORT Point : public Shape
		{
			double x, y;

			Point(double x, double y) : x(x), y(y)
			{}

			virtual double const Area()
			{
				return 0;
			}
		};
	}
}