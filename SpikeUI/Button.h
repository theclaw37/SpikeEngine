#pragma once

#include <functional>
#include "TextArea.h"
#include "Rectangle.h"
#include "Drawable.h"

namespace SpikeUI
{
	namespace Controls
	{
		struct __declspec(dllexport) Button : SpikeUI::UI::Drawable
		{
			SpikeUI::Containers::Rectangle Place;
			SpikeUI::Colour::Colour Colour;

			std::function<void(Button &)> receiveFocus, loseFocus, lClickDown, lClickUp;

			Button(SpikeUI::Containers::Rectangle const &,
				SpikeUI::Colour::Colour const &);

			virtual void MouseUpdate(bool, bool);
			virtual void Update();
			virtual bool Contains(SpikeUI::Containers::Point const &);
			virtual void ReceiveFocus();
			virtual void LoseFocus();
			virtual void LeftClickDown();
			virtual void LeftClickUp();
			virtual ~Button() = default;
		};
	}
}