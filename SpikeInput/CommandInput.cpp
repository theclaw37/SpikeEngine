#include "CommandInput.h"

SpikeInput::CommandOutput SpikeInput::CommandInput::GetCommandInput()
{
	auto copy = _CIOutput;
	_CIOutput = CommandNone;
	return copy;
}

void SpikeInput::CommandInput::PushCommandInput(CommandOutput input)
{
	_CIOutput = input;
}

void SpikeInput::CommandInput::PopCommandInput()
{
	_CIOutput = CommandNone;
}
