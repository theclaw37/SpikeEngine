#include "Button.h"

#include <Windows.h>

SpikeUI::Controls::Button::Button(SpikeUI::Containers::Rectangle const & place,
	SpikeUI::Colour::Colour const & colour) :
	Place(place),
	Colour(colour),
	Drawable(SpikeUI::UI::DrawableType::Button)
{
	DHit = SpikeUI::UI::DrawableHit::Enable;
}

void SpikeUI::Controls::Button::MouseUpdate(bool leftClickDown, bool leftClickUp)
{
	if (leftClickDown)
		LeftClickDown();
	else if (leftClickUp)
		LeftClickUp();
}

void SpikeUI::Controls::Button::Update()
{
}

bool SpikeUI::Controls::Button::Contains(SpikeUI::Containers::Point const & mouse)
{
	return Place.Contains(mouse);
}

void SpikeUI::Controls::Button::ReceiveFocus()
{
	DState = SpikeUI::UI::DrawableState::Hover;

	if (receiveFocus)
		receiveFocus(*this);
}

void SpikeUI::Controls::Button::LoseFocus()
{
	DState = SpikeUI::UI::DrawableState::Default;

	if (receiveFocus)
		loseFocus(*this);
}

void SpikeUI::Controls::Button::LeftClickDown()
{
	if (lClickDown)
		lClickDown(*this);
}

void SpikeUI::Controls::Button::LeftClickUp()
{
	if (lClickUp)
		lClickUp(*this);
}
