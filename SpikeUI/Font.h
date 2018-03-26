#pragma once

#include <iostream>

namespace SpikeUI
{
	namespace Containers
	{
		struct __declspec(dllexport) Font
		{
			std::string FontFamily;
			unsigned int Size;

			Font(std::string const & family, unsigned int size) : FontFamily(family), Size(size)
			{}
		};
	}
}