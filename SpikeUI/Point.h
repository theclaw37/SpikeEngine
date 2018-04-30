#pragma once

#include <algorithm>
#include "Shape.h"
#include "SpikeUtils.h"

namespace SpikeUI
{
	namespace Containers
	{
		struct Point : public Shape
		{
			double x, y;

			Point(double x, double y) : x(x), y(y)
			{}

			Point& ClampToPercentage()
			{
				x = CLAMP(x, 0.0, 1.0);
				y = CLAMP(y, 0.0, 1.0);

				return (*this);
			}

			friend Point operator-(Point lhs, Point const & rhs)
			{
				lhs -= rhs;
				return lhs;
			}

			friend Point operator+(Point lhs, Point const & rhs)
			{
				lhs += rhs;
				return lhs;
			}

			Point& operator-=(Point const & rhs)
			{
				x -= rhs.x;
				y -= rhs.y;
				return *this;
			}

			Point& operator+=(Point const & rhs)
			{
				x += rhs.x;
				y += rhs.y;
				return *this;
			}
		};
	}
}