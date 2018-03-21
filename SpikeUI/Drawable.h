#pragma once

#include <memory>
#include "Point.h"
#include "GUIDREF.h"

namespace SpikeUI
{
	namespace UI
	{
		enum DrawableType
		{
			TextArea = 0
		};

		enum DrawableState
		{
			Default = 0,
			Hover = 1
		};

		struct __declspec(dllexport) Drawable : SpikeUtils::GUIDREF
		{
			DrawableType Type;
			DrawableState State;

			Drawable(DrawableType type) : Type(type)
			{}

			virtual bool HandleMouse(SpikeUI::Containers::Point, bool, bool) = 0;
			virtual void ReceiveFocus() = 0;
			virtual void LoseFocus() = 0;
			virtual void LeftClickDown() = 0;
			virtual void LeftClickUp() = 0;
			virtual ~Drawable() = default;
		};
	}
}