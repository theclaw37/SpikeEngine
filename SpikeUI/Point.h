#pragma once

#include "Shape.h"

namespace SpikeUI
{
	namespace Containers
	{
		struct __declspec(dllexport) Point : Shape
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