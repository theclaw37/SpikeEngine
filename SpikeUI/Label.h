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
		struct SPIKEUI_EXPORT Label : SpikeUI::UI::Drawable
		{
			SpikeUI::Containers::Rectangle Place;
			SpikeUI::Containers::Font Font;
			SpikeUI::Colour::Colour Colour;
			std::string Text;

			std::function<void(Label &)> hoverIn, hoverOut, lButtonDown, lButtonUp, rButtonDown, rButtonUp;;
			std::function<void(Label &, SpikeUI::Containers::Key const &)> receiveKey;

			Label(SpikeUI::Containers::Rectangle const &,
				SpikeUI::Containers::Font const &,
				SpikeUI::Colour::Colour const &);

			virtual void PointerUpdate(bool, bool, bool, bool);
			virtual void Update();
			virtual bool Contains(SpikeUI::Containers::Point const &);
			virtual void MoveByPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point MoveToPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point RelativePixelDelta(SpikeUI::Containers::Point const &);
			virtual void HoverIn();
			virtual void HoverOut();
			virtual ~Label() = default;
		};
	}
}