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

			inline double Width() const
			{
				return (BottomRight.x - TopLeft.x);
			}

			inline double Height() const
			{
				return (BottomRight.y - TopLeft.y);
			}

			inline Point RelativeToAbsolute(Point const & relativeCoords) const
			{
				return SpikeUI::Containers::Point(
					TopLeft.x + relativeCoords.x * Width(),
					TopLeft.y + relativeCoords.y * Height());
			}

			inline Rectangle RelativeMoveToAbsolute(Point const & relativeCoords)
			{
				auto topLeft = RelativeToAbsolute(relativeCoords);
				return Rectangle(
					topLeft.x,
					topLeft.y,
					topLeft.x + Width(),
					topLeft.y + Height()
				);
			}

			friend Rectangle operator-(Rectangle lhs, Point const & rhs)
			{
				lhs -= rhs;
				return lhs;
			}

			friend Rectangle operator+(Rectangle lhs, Point const & rhs)
			{
				lhs += rhs;
				return lhs;
			}

			Rectangle& operator-=(Point const & rhs)
			{
				TopLeft -= rhs;
				BottomRight -= rhs;
				return (*this);
			}

			Rectangle& operator+=(Point const & rhs)
			{
				TopLeft += rhs;
				BottomRight += rhs;
				return (*this);
			}
		};
	}
}