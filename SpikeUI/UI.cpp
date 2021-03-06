#include <algorithm>
#include "UI.h"
#include "Drawable.h"
#include "EmptyArea.h"

#include <windows.h>

SpikeUI::UI::UI::UI() : _UIState(UIState::Initial)
{}

void SpikeUI::UI::UI::Init(SpikeUI::Containers::Rectangle const & rootArea)
{
	_UIRoot = std::make_shared<SpikeUI::Controls::EmptyArea>(rootArea, "ui_root");
	_UIState = UIState::Ready;
}

std::shared_ptr<SpikeUI::UI::Drawable> SpikeUI::UI::UI::GetByGuid(SpikeUtils::GUID const & guid)
{
	auto elem = _UIElems.find(guid);
	if (elem != _UIElems.end())
	{
		return elem->second;
	}

	return nullptr;
}

std::shared_ptr<SpikeUI::UI::Drawable> SpikeUI::UI::UI::GetById(std::string const & id)
{
	auto elem = _UIElemsById.find(id);
	if (elem != _UIElemsById.end())
	{
		return elem->second;
	}

	return nullptr;
}

void SpikeUI::UI::UI::MoveTo(std::shared_ptr<SpikeUI::UI::Drawable> target, SpikeUI::Containers::Point const & position)
{
	if (&(*target) != &(*_UIRoot))
	{
		auto positionPercentage(position);
		positionPercentage.ClampToPercentage();

		auto movedTo = target->DParent->RelativePixelDelta(positionPercentage);
		auto deltaPixels = target->MoveToPixels(movedTo);
		IterateBackToFront(target, [&deltaPixels](std::shared_ptr<SpikeUI::UI::Drawable> child) {
			child->MoveByPixels(deltaPixels);
		});
	}
}

void SpikeUI::UI::UI::MoveBy(std::shared_ptr<SpikeUI::UI::Drawable> target, SpikeUI::Containers::Point const & position)
{
	if (&(*target) != &(*_UIRoot))
	{
		auto positionPercentage(position);
		positionPercentage.ClampToPercentage();

		auto movedBy = target->DParent->RelativePixelDelta(positionPercentage);
		target->MoveByPixels(movedBy);
		IterateBackToFront(target, [&movedBy](std::shared_ptr<SpikeUI::UI::Drawable> child) {
			child->MoveByPixels(movedBy);
		});
	}
}

void SpikeUI::UI::UI::Erase(std::string const & identifier)
{
	auto node = GetById(identifier);
	Erase(node);
}

void SpikeUI::UI::UI::Erase(SpikeUtils::GUID const & guid)
{
	auto node = GetByGuid(guid);
	Erase(node);
}

void SpikeUI::UI::UI::Erase(
	std::shared_ptr<SpikeUI::UI::Drawable> target)
{
	if (!target)
		return;

	auto& siblings = target->DParent->DChildren;
	siblings.erase(
		std::remove(siblings.begin(), siblings.end(), target));

	_UIElems.erase(target->_SpikeEngineId());
	_UIElemsById.erase(target->_SpikeObjectId());
}

void SpikeUI::UI::UI::IterateBackToFront(
	std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)> functor)
{
	IterateBackToFront(_UIRoot, functor);
}

void SpikeUI::UI::UI::IterateBackToFront(
	std::shared_ptr<SpikeUI::UI::Drawable> drawable, 
	std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)> functor)
{
	for (auto & iter : drawable->DChildren)
	{
		functor(iter);
		IterateBackToFront(iter, functor);
	}
}

void SpikeUI::UI::UI::IterateFrontToBack(
	std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)> functor)
{
	IterateFrontToBack(_UIRoot, functor);
}

void SpikeUI::UI::UI::IterateFrontToBack(
	std::shared_ptr<SpikeUI::UI::Drawable> drawable, 
	std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)> functor)
{
	for (auto iter = drawable->DChildren.rbegin(); iter != drawable->DChildren.rend(); ++iter)
	{
		IterateFrontToBack(*iter, functor);
		functor(*iter);
	}
}

void SpikeUI::UI::UI::UpdateForPointer(
	SpikeUI::Containers::Point const & mouse, 
	bool lButtonDown, 
	bool lButtonUp,
	bool rButtonDown,
	bool rButtonUp)
{
	std::shared_ptr<SpikeUI::UI::Drawable> focus = nullptr;
	IterateFrontToBack(_UIRoot, 
		[&focus, 
		&mouse, 
		&lButtonDown, 
		&lButtonUp, 
		&rButtonDown, 
		&rButtonUp](std::shared_ptr<SpikeUI::UI::Drawable> drawable)
	{
		if (!focus)
		{
			if (drawable->DHit == SpikeUI::UI::DrawableHit::HitEnable && drawable->Contains(mouse))
			{
				focus = drawable;
				drawable->PointerUpdate(lButtonDown, 
					lButtonUp,
					rButtonDown,
					rButtonUp);
			}
		}
		drawable->Update();
	});

	SwitchHover(focus);

	if (lButtonUp)
		SwitchFocus(focus);
}

void SpikeUI::UI::UI::UpdateForCharacterInput(SpikeUI::Containers::Key const & msg)
{
	if (_UIFocus)
		_UIFocus->KeyInput(msg);
}

std::shared_ptr<SpikeUI::UI::Drawable> SpikeUI::UI::UI::GetFocusedItem() const
{
	return _UIFocus;
}

SpikeUI::UI::UIState SpikeUI::UI::UI::GetState() const
{
	return _UIState;
}

void SpikeUI::UI::UI::SwitchHover(std::shared_ptr<SpikeUI::UI::Drawable> target)
{
	if (_UIHover)
	{
		_UIHover->HoverOut();
	}

	if (target)
	{
		target->HoverIn();
	}
	_UIHover = target;
}

void SpikeUI::UI::UI::SwitchFocus(std::shared_ptr<SpikeUI::UI::Drawable> target)
{
	if (_UIFocus)
		_UIFocus->Unfocus();

	if (target)
	{
		target->Focus();
	}
	_UIFocus = target;
}

