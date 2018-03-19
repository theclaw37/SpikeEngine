#pragma once

#include "GUIDREF.h"

namespace SpikeUI
{
	namespace UI
	{
		enum DrawableType
		{
			TextArea = 0
		};

		struct __declspec(dllexport) Drawable : SpikeUtils::GUIDREF
		{
			DrawableType Type;

			Drawable(DrawableType type) : Type(type)
			{}
		};
	}
}