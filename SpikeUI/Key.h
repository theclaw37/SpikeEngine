#pragma once

namespace SpikeUI
{
	namespace Containers
	{
		using KeyCharacterInput = char;
		enum KeyCharacterControlInput
		{
			None = 0,
			Backspace = 1,
			Space = 2,
			Tab = 4,
			Enter = 8,
			Left = 16,
			Right = 32,
			Up = 64,
			Down = 128
		};

		struct Key
		{
			char Character;
			KeyCharacterControlInput CharacterControl;

			Key(char character, KeyCharacterControlInput control) : 
				Character(character), 
				CharacterControl(control)
			{}

			static Key CharacterKey(char & character)
			{
				return Key(character, None);
			}

			static Key ControlKey(KeyCharacterControlInput control)
			{
				return Key(0, control);
			}

			bool IsCharacter() const
			{
				return Character;
			}
		};
	}
}