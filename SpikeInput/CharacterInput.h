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
	using SequenceCharacterOutput = std::string;
	using PipeCharacterInput = char;

	class SPIKEINPUT_EXPORT CharacterInput : public SpikeUtils::Singleton<CharacterInput>
	{
	public:
		SequenceCharacterOutput GetCharacterInput();
		void PushCharacterInput(PipeCharacterInput);
		void PopCharacterInput();
	private:
		SequenceCharacterOutput _CIOutput;
	};
}