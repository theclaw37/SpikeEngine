#pragma once

#include <functional>
#include "Rectangle.h"
#include "Font.h"
#include "Drawable.h"
#include "Colour.h"
#include "Key.h"

#ifdef DLL_SPIKEUI
#define SPIKEUI_EXPORT __declspec(dllexport)
#else
#define SPIKEUI_EXPORT __declspec(dllimport)
#endif

namespace SpikeUI
{
	namespace Controls
	{
		struct SPIKEUI_EXPORT TextArea : SpikeUI::UI::Drawable
		{
			SpikeUI::Containers::Rectangle Place;
			SpikeUI::Containers::Font Font;
			SpikeUI::Colour::Colour TextColour;
			SpikeUI::Colour::Colour BackgroundColour;
			std::string Text;

			std::function<void(TextArea &)> hoverIn, hoverOut, lButtonDown, lButtonUp, rButtonDown, rButtonUp;;
			std::function<void(TextArea &, SpikeUI::Containers::Key const &)> receiveKey;

			TextArea(SpikeUI::Containers::Rectangle const &,
				SpikeUI::Containers::Font const &,
				SpikeUI::Colour::Colour const &,
				SpikeUI::Colour::Colour const &,
				std::string const &);

			virtual void PointerUpdate(bool, bool, bool, bool);
			virtual void KeyInput(SpikeUI::Containers::Key const &);
			virtual void Update();
			virtual bool Contains(SpikeUI::Containers::Point const &);
			virtual void MoveByPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point MoveToPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point RelativePixelDelta(SpikeUI::Containers::Point const &);
			virtual void HoverIn();
			virtual void HoverOut();
			virtual void Focus();
			virtual void Unfocus();
			virtual ~TextArea() = default;
		};
	}
}