#pragma once

#include "Point.h"

namespace SpikeUI
{
	namespace Containers
	{
		struct __declspec(dllexport) Rectangle : Shape
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