#pragma once

#ifdef DLL_SPIKEUI
#define SPIKEUI_EXPORT __declspec(dllexport)
#else
#define SPIKEUI_EXPORT __declspec(dllimport)
#endif

namespace SpikeUI
{
	namespace Containers
	{
		struct SPIKEUI_EXPORT Key
		{
			char ch;

			Key(char ch) : ch(ch)
			{}
		};
	}
}