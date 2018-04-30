#pragma once

#include <string>

namespace SpikeUI
{
	namespace Containers
	{
		struct Font
		{
			std::string FontFamily;
			unsigned int Size;

			Font(std::string const & family, unsigned int size) : FontFamily(family), Size(size)
			{}
		};
	}
}