#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "SpikeUtils.h"

#ifdef DLL_SPIKEINPUT
#define SPIKEINPUT_EXPORT __declspec(dllexport)
#else
#define SPIKEINPUT_EXPORT __declspec(dllimport)
#endif

namespace SpikeInput
{
	enum CommandOutput
	{
		CommandNone = 0,
		CommandBackspace = 1,
		CommandEnter = 2,
		CommandLeft = 4,
		CommandRight = 8,
		CommandUp = 16,
		CommandDown = 32,
		CommandSpace = 64
	};

	class SPIKEINPUT_EXPORT CommandInput : public SpikeUtils::Singleton<CommandInput>
	{
	public:
		CommandOutput GetCommandInput();
		void PushCommandInput(CommandOutput);
		void PopCommandInput();
	private:
		CommandOutput _CIOutput;
	};
}