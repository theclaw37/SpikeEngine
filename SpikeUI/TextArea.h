#pragma once

#include <functional>
#include "Rectangle.h"
#include "Font.h"
#include "Drawable.h"
#include "Colour.h"

namespace SpikeUI
{
	namespace Controls
	{
		struct __declspec(dllexport) TextArea : SpikeUI::UI::Drawable
		{
			SpikeUI::Containers::Rectangle Place;
			SpikeUI::Containers::Font Font;
			SpikeUI::Colour::Colour Colour;
			std::string Text;

			std::function<void(TextArea &)> receiveFocus, loseFocus, lClickDown, lClickUp;

			TextArea(SpikeUI::Containers::Rectangle const &,
				SpikeUI::Containers::Font const &,
				SpikeUI::Colour::Colour const &);

			virtual void MouseUpdate(bool, bool);
			virtual void Update();
			virtual bool Contains(SpikeUI::Containers::Point const &);
			virtual void ReceiveFocus();
			virtual void LoseFocus();
			virtual void LeftClickDown();
			virtual void LeftClickUp();
			virtual ~TextArea() = default;
		};
	}
}