#include "UI.h"
#include "Drawable.h"
#include <algorithm>

void SpikeUI::UI::UI::Erase(std::string const & guid)
{
	UIContainer.erase(
		std::remove_if(
			UIContainer.begin(), 
			UIContainer.end(),
			[guid](auto elem)
			{
				return elem->_SpikeEngineId() == guid;
			}));
}

void SpikeUI::UI::UI::Iterate(std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)> functor)
{
	for (auto & iter : UIContainer)
	{
		functor(iter);
	}
}

std::shared_ptr<SpikeUI::UI::Drawable> SpikeUI::UI::UI::Mouse(SpikeUI::Containers::Point position, bool leftClickDown, bool leftClickUp)
{
	for (auto & iter : UIContainer)
	{
		if (iter->HandleMouse(position, leftClickDown, leftClickUp))
		{
			SwitchFocus(iter);
			return iter;
		}
	}

	SwitchFocus(nullptr);
	return nullptr;
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
