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

			TextArea(SpikeUI::Containers::Rectangle const &,
				SpikeUI::Text::Font const &,
				SpikeUI::Colour::Colour const &);

			virtual bool HandleMouse(SpikeUI::Containers::Point, bool, bool);
			virtual void ReceiveFocus();
			virtual void LoseFocus();
			virtual void LeftClickDown();
			virtual void LeftClickUp();
			virtual ~TextArea() = default;
		};
	}
}