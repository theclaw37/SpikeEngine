#include "TextArea.h"

SpikeUI::Controls::TextArea::TextArea(SpikeUI::Containers::Rectangle const & place, 
	SpikeUI::Containers::Font const & font, 
	SpikeUI::Colour::Colour const & colour) : 
		Place(place), 
		Font(font), 
		Colour(colour),
		Drawable(SpikeUI::UI::DrawableType::TextArea)
{
	DHit = SpikeUI::UI::DrawableHit::Disable;
}

void SpikeUI::Controls::TextArea::MouseUpdate(bool leftClickDown, bool leftClickUp)
{
	if (leftClickDown)
		LeftClickDown();
	else if (leftClickUp)
		LeftClickUp();
}

void SpikeUI::Controls::TextArea::Update()
{
}

bool SpikeUI::Controls::TextArea::Contains(SpikeUI::Containers::Point const & mouse)
{
	return Place.Contains(mouse);
}

void SpikeUI::Controls::TextArea::ReceiveFocus()
{
	DState = SpikeUI::UI::DrawableState::Hover;
	
	if (receiveFocus)
		receiveFocus(*this);
}

void SpikeUI::Controls::TextArea::LoseFocus()
{
	DState = SpikeUI::UI::DrawableState::Default;

	if (receiveFocus)
		loseFocus(*this);
}

void SpikeUI::Controls::TextArea::LeftClickDown()
{
	if (lClickDown)
		lClickDown(*this);
}

void SpikeUI::Controls::TextArea::LeftClickUp()
{
	if (lClickUp)
		lClickUp(*this);
}
