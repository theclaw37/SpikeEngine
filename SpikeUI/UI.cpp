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
				return (*elem)._SpikeEngineId() == guid;
			}));
	Reset();
}

void SpikeUI::UI::UI::Reset()
{
	UIContainerIterator = UIContainer.begin();
}

SpikeUI::UI::DrawableType SpikeUI::UI::UI::GetType()
{
	return (**UIContainerIterator).Type;
}

bool SpikeUI::UI::UI::Iterate()
{
	return (++UIContainerIterator != UIContainer.end());
}
