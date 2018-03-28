#pragma once

#include "Point.h"

#ifdef DLL_SPIKEUI
#define SPIKEUI_EXPORT __declspec(dllexport)
#else
#define SPIKEUI_EXPORT __declspec(dllimport)
#endif

namespace SpikeUI
{
	namespace Containers
	{
		struct SPIKEUI_EXPORT Rectangle : public Shape
		{
			Point TopLeft, BottomRight;

			Rectangle(double tlX, double tlY, double brX, double brY) : TopLeft{ tlX, tlY }, BottomRight{ brX, brY }
			{}

			inline bool Contains(SpikeUI::Containers::Point const & point)
			{
				return (point.x >= TopLeft.x)
					&& (point.x <= BottomRight.x)
					&& (point.y >= TopLeft.y)
					&& (point.y <= BottomRight.y);
			}
		};
	}
}