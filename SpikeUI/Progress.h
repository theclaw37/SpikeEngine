#pragma once

#include <functional>
#include "Colour.h"
#include "Rectangle.h"
#include "Drawable.h"

#ifdef DLL_SPIKEUI
#define SPIKEUI_EXPORT __declspec(dllexport)
#else
#define SPIKEUI_EXPORT __declspec(dllimport)
#endif

namespace SpikeUI
{
	namespace Controls
	{
		struct SPIKEUI_EXPORT Progress : SpikeUI::UI::Drawable
		{
			SpikeUI::Containers::Rectangle Place;
			SpikeUI::Colour::Colour FillColour;
			SpikeUI::Colour::Colour EmptyColour;
			double Value;

			Progress(SpikeUI::Containers::Rectangle const &,
				SpikeUI::Colour::Colour const &,
				SpikeUI::Colour::Colour const &);

			void SetProgress(double value);
			void IncreaseProgress(double value);
			double GetValueCoord() const;
			virtual void PointerUpdate(bool, bool);
			virtual void Update();
			virtual bool Contains(SpikeUI::Containers::Point const &);
			virtual void MoveByPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point MoveToPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point RelativePixelDelta(SpikeUI::Containers::Point const &);
			virtual ~Progress() = default;
		};
	}
}