#pragma once

#include "Rectangle.h"
#include "Font.h"
#include "Drawable.h"
#include "Colour.h"

namespace SpikeUI
{
	namespace Text
	{
		struct __declspec(dllexport) TextArea : SpikeUI::UI::Drawable
		{
			SpikeUI::Containers::Rectangle Place;
			SpikeUI::Text::Font Font;
			SpikeUI::Colour::Colour Colour;
			std::string Text;

			TextArea(SpikeUI::Containers::Rectangle const & place,
				SpikeUI::Text::Font const & font,
				SpikeUI::Colour::Colour const & colour);

		};
	}
}