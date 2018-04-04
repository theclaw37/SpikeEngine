#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "SpikeUtils.h"
#include "SpikeUI.h"

#ifdef DLL_SPIKEINPUT
#define SPIKEINPUT_EXPORT __declspec(dllexport)
#else
#define SPIKEINPUT_EXPORT __declspec(dllimport)
#endif

namespace SpikeInput
{
	struct SPIKEINPUT_EXPORT MouseOutput
	{
		SpikeUI::Containers::Point MOCoords;
		bool MOLeftButtonDown, MOLeftButtonUp, MORightButtonDown, MORightButtonUp;
	};

	class SPIKEINPUT_EXPORT MouseInput : public SpikeUtils::Singleton<MouseInput>
	{
	public:
#ifdef _WIN32
		MouseOutput GetAbsoluteMouse(HWND);
#endif
	};
}