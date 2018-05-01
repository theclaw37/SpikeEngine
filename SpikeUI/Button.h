#pragma once

#include <functional>
#include "Colour.h"
#include "Rectangle.h"
#include "Drawable.h"
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
		struct SPIKEUI_EXPORT Button : public SpikeUI::UI::Drawable
		{
			SpikeUI::Containers::Rectangle Place;
			std::shared_ptr<SpikeUI::Colour> Colour;

			std::function<void(Button &)> hoverIn, hoverOut, lButtonDown, lButtonUp, rButtonDown, rButtonUp;
			std::function<void(Button &, SpikeUI::Containers::Key const &)> receiveKey;

			Button(SpikeUI::Containers::Rectangle const &,
				std::shared_ptr<SpikeUI::Colour> colour,
				std::string const &);

			virtual void PointerUpdate(bool, bool, bool, bool);
			virtual void Update();
			virtual bool Contains(SpikeUI::Containers::Point const &);
			virtual void MoveByPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point MoveToPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point RelativePixelDelta(SpikeUI::Containers::Point const &);
			virtual void HoverIn();
			virtual void HoverOut();
			virtual ~Button() = default;
		};
	}
}