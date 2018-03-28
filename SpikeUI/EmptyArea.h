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

			virtual void MouseUpdate(bool, bool);
			virtual void KeyboardUpdate(SpikeUI::Containers::Key const &);
			virtual void Update();
			virtual bool Contains(SpikeUI::Containers::Point const &);
			virtual void ReceiveFocus();
			virtual void LoseFocus();
			virtual void LeftClickDown();
			virtual void LeftClickUp();
			virtual ~EmptyArea() = default;
		};
	}
}