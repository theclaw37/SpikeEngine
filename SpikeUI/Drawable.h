#pragma once

#include <memory>
#include <deque>
#include "Point.h"
#include "Key.h"
#include "SpikeUtils.h"

#ifdef DLL_SPIKEUI
#define SPIKEUI_EXPORT __declspec(dllexport)
#else
#define SPIKEUI_EXPORT __declspec(dllimport)
#endif

namespace SpikeUI
{
	namespace UI
	{
		enum DrawableType
		{
			TextArea = 1,
			Button = 2,
			EmptyArea = 4,

		};

		enum DrawableState
		{
			Default = 1,
			Hover = 2
		};

		enum DrawableHit
		{
			Enable = 1,
			Disable = 2
		};

		struct SPIKEUI_EXPORT Drawable : SpikeUtils::_SpikeEngineObject
		{
			DrawableType DType;
			DrawableState DState;
			DrawableHit DHit;

			Drawable(DrawableType type) : DType(type)
			{}

			std::shared_ptr<Drawable> DParent;
			std::deque<std::shared_ptr<Drawable>> DChildren;

			virtual void MouseUpdate(bool, bool) = 0;
			virtual void KeyboardUpdate(SpikeUI::Containers::Key const &) = 0;
			virtual void Update() = 0;
			virtual bool Contains(SpikeUI::Containers::Point const &) = 0;
			virtual void MoveByPixels(SpikeUI::Containers::Point const &) = 0;
			virtual SpikeUI::Containers::Point MoveToPixels(SpikeUI::Containers::Point const &) = 0;
			virtual SpikeUI::Containers::Point RelativePixelDelta(SpikeUI::Containers::Point const &) = 0;
			virtual void ReceiveFocus() = 0;
			virtual void LoseFocus() = 0;
			virtual void LeftClickDown() = 0;
			virtual void LeftClickUp() = 0;
			virtual ~Drawable() = default;
		};
	}
}