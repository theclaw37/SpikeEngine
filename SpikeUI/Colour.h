#pragma once

#include <iostream>

namespace SpikeUI
{
	namespace Colour
	{
		struct __declspec(dllexport) Colour
		{
			double r, g, b;

			Colour(double r, double g, double b) : r(r), g(g), b(b)
			{}
		};
	}
}