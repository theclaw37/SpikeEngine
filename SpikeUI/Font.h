#pragma once

#include <string>

#ifdef DLL_SPIKEUI
#define SPIKEUI_EXPORT __declspec(dllexport)
#else
#define SPIKEUI_EXPORT __declspec(dllimport)
#endif

namespace SpikeUI
{
	namespace Containers
	{
		struct SPIKEUI_EXPORT Font
		{
			std::string FontFamily;
			unsigned int Size;

			Font(std::string const & family, unsigned int size) : FontFamily(family), Size(size)
			{}
		};
	}
}