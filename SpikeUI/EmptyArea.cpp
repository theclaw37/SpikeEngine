#include "EmptyArea.h"

SpikeUI::Controls::EmptyArea::EmptyArea(SpikeUI::Containers::Rectangle const & place) :
	Place(place),
	Drawable(SpikeUI::UI::DrawableType::EmptyArea)
{
	DHit = SpikeUI::UI::DrawableHit::Disable;
}

void SpikeUI::Controls::EmptyArea::MouseUpdate(bool leftClickDown, bool leftClickUp)
{
}

void SpikeUI::Controls::EmptyArea::Update()
{
}

bool SpikeUI::Controls::EmptyArea::Contains(SpikeUI::Containers::Point const & mouse)
{
	return Place.Contains(mouse);
}

void SpikeUI::Controls::EmptyArea::ReceiveFocus()
{
}

void SpikeUI::Controls::EmptyArea::LoseFocus()
{
}

void SpikeUI::Controls::EmptyArea::LeftClickDown()
{
}

void SpikeUI::Controls::EmptyArea::LeftClickUp()
{
}