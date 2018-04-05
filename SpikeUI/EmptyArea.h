#pragma once

#include <functional>
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
		struct SPIKEUI_EXPORT EmptyArea : SpikeUI::UI::Drawable
		{
			SpikeUI::Containers::Rectangle Place;

			EmptyArea(SpikeUI::Containers::Rectangle const &);

			virtual bool Contains(SpikeUI::Containers::Point const &);
			virtual void MoveByPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point MoveToPixels(SpikeUI::Containers::Point const &);
			virtual SpikeUI::Containers::Point RelativePixelDelta(SpikeUI::Containers::Point const &);
			virtual ~EmptyArea() = default;
		};
	}
}