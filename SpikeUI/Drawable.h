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
			Label = 1,
			Button = 2,
			EmptyArea = 4,
			Progress = 8,
			TextArea = 16
		};

		enum DrawableHoverState
		{
			HoverDefault = 1,
			HoverActive = 2
		};

		enum DrawableFocusState
		{
			FocusDefault = 1,
			FocusActive = 2
		};

		enum DrawableHit
		{
			HitEnable = 1,
			HitDisable = 2
		};

		struct SPIKEUI_EXPORT Drawable : SpikeUtils::_SpikeEngineObject
		{
			DrawableType DType;
			DrawableHoverState DHoverState;
			DrawableFocusState DFocusState;
			DrawableHit DHit;

			Drawable(DrawableType type, std::string const & id) : DType(type), _SpikeEngineObject(id)
			{}

			std::shared_ptr<Drawable> DParent;
			std::deque<std::shared_ptr<Drawable>> DChildren;

			virtual void PointerUpdate(bool, bool, bool, bool) {};
			virtual void KeyInput(SpikeUI::Containers::Key const &) {};
			virtual void Update() {};
			virtual bool Contains(SpikeUI::Containers::Point const &) = 0;
			virtual void MoveByPixels(SpikeUI::Containers::Point const &) = 0;
			virtual SpikeUI::Containers::Point MoveToPixels(SpikeUI::Containers::Point const &) = 0;
			virtual SpikeUI::Containers::Point RelativePixelDelta(SpikeUI::Containers::Point const &) = 0;
			virtual void HoverIn() { DHoverState = HoverDefault; };
			virtual void HoverOut() { DHoverState = HoverActive; };
			virtual void Focus() { DFocusState = FocusDefault; };
			virtual void Unfocus() { DFocusState = FocusActive; };
			virtual ~Drawable() = default;
		};
	}
}