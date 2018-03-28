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
			SpikeUI::Colour::Colour Colour;

			std::function<void(Button &)> receiveFocus, loseFocus, lClickDown, lClickUp;
			std::function<void(Button &, SpikeUI::Containers::Key const &)> receiveKey;

			Button(SpikeUI::Containers::Rectangle const &,
				SpikeUI::Colour::Colour const &);

			virtual void MouseUpdate(bool, bool);
			virtual void KeyboardUpdate(SpikeUI::Containers::Key const &);
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