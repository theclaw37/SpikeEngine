#pragma once

#include "Point.h"

namespace SpikeUI
{
	namespace Containers
	{
		struct __declspec(dllexport) Rectangle
		{
			Point TopLeft, BottomRight;

			Rectangle(double tlX, double tlY, double brX, double brY) : TopLeft{ tlX, tlY }, BottomRight{ brX, brY }
			{}

			virtual double const Area()
			{
				return (BottomRight.x - TopLeft.x) * (BottomRight.y - TopLeft.y);
			}
		};
	}
}