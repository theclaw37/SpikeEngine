#include <algorithm>
#include "UI.h"
#include "Drawable.h"
#include "EmptyArea.h"


SpikeUI::UI::UI::UI(SpikeUI::Containers::Rectangle const & rootArea) : 
	UIRoot(std::make_shared<SpikeUI::Controls::EmptyArea>(rootArea))
{}

std::shared_ptr<SpikeUI::UI::Drawable> SpikeUI::UI::UI::Get(std::string const & guid)
{
	auto elem = UIElems.find(guid);
	if (elem != UIElems.end())
	{
		return elem->second;
	}

	return nullptr;
}

void SpikeUI::UI::UI::Erase(std::string const & guid)
{
	Erase(UIRoot, guid);
}

void SpikeUI::UI::UI::Erase(
	std::shared_ptr<SpikeUI::UI::Drawable> target, 
	std::string const & guid)
{
	auto childrenSize = target->DChildren.size();

	if (childrenSize > 0)
	{
		target->DChildren.erase(
			std::remove_if(
				target->DChildren.begin(),
				target->DChildren.end(),
				[guid](auto elem)
		{
			return elem->_SpikeEngineId() == guid;
		}));

		if (target->DChildren.size() == childrenSize)
		{
			for (auto & child : target->DChildren)
			{
				Erase(child, guid);
			}
		}
		else
		{
			UIElems.erase(guid);
		}
	}
}


void SpikeUI::UI::UI::IterateBackToFront(
	std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)> functor)
{
	IterateBackToFront(UIRoot, functor);
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
	IterateFrontToBack(UIRoot, functor);
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

void SpikeUI::UI::UI::Update(
	SpikeUI::Containers::Point const & mouse, 
	bool leftClickDown, 
	bool leftClickUp)
{
	std::shared_ptr<SpikeUI::UI::Drawable> focus = nullptr;
	IterateFrontToBack(UIRoot, 
		[&focus, &mouse, &leftClickDown, &leftClickUp](std::shared_ptr<SpikeUI::UI::Drawable> drawable) 
	{
		if (!focus)
		{
			if (drawable->DHit == SpikeUI::UI::DrawableHit::Enable && drawable->Contains(mouse))
			{
				focus = drawable;
				drawable->MouseUpdate(leftClickDown, leftClickUp);
			}
		}
		drawable->Update();
	});

	SwitchFocus(focus);
}

void SpikeUI::UI::UI::SwitchFocus(std::shared_ptr<SpikeUI::UI::Drawable> target)
{
	if (UIFocus) 
		UIFocus->LoseFocus();

	if (target)
	{
		target->ReceiveFocus();
		UIFocus = target;
	}
}

