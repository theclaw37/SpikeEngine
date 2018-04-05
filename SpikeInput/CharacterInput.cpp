#include "CharacterInput.h"

SpikeInput::SequenceCharacterOutput SpikeInput::CharacterInput::GetCharacterInput()
{
	auto copy = _CIOutput;
	_CIOutput = 0;
	return copy;
}

void SpikeInput::CharacterInput::PushCharacterInput(PipeCharacterInput input)
{
	_CIOutput = input;
}

void SpikeInput::CharacterInput::PopCharacterInput()
{
	_CIOutput = 0;
}
