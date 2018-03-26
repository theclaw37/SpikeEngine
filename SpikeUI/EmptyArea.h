#pragma once

#include <functional>
#include "Rectangle.h"
#include "Drawable.h"

namespace SpikeUI
{
	namespace Controls
	{
		struct __declspec(dllexport) EmptyArea : SpikeUI::UI::Drawable
		{
			SpikeUI::Containers::Rectangle Place;

			EmptyArea(SpikeUI::Containers::Rectangle const &);

			virtual void MouseUpdate(bool, bool);
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