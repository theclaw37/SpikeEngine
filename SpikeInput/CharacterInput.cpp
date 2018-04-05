#include "CharacterInput.h"

SpikeInput::SequenceCharacterOutput SpikeInput::CharacterInput::GetCharacterInput()
{
	auto copy = _CIOutput;
	_CIOutput.clear();
	return copy;
}

void SpikeInput::CharacterInput::PushCharacterInput(PipeCharacterInput input)
{
	_CIOutput += input;
}

void SpikeInput::CharacterInput::PopCharacterInput()
{
	if (!_CIOutput.empty())
		_CIOutput.pop_back();
}
