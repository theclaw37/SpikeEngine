#include "Button.h"

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

void SpikeUI::Controls::Button::KeyboardUpdate(SpikeUI::Containers::Key const & key)
{
	if (receiveKey)
		receiveKey(*this, key);
}

void SpikeUI::Controls::Button::Update()
{
}

bool SpikeUI::Controls::Button::Contains(SpikeUI::Containers::Point const & mouse)
{
	return Place.Contains(mouse);
}

void SpikeUI::Controls::Button::MoveByPixels(SpikeUI::Containers::Point const & pixels)
{
	Place += pixels;
}

SpikeUI::Containers::Point SpikeUI::Controls::Button::MoveToPixels(SpikeUI::Containers::Point const & pixels)
{
	auto width = Place.Width();
	auto height = Place.Height();
	auto newPlace = SpikeUI::Containers::Rectangle(pixels.x, pixels.y, pixels.x + width, pixels.y + height);
	auto delta = newPlace.TopLeft - Place.TopLeft;
	Place = newPlace;
	return delta;
}

SpikeUI::Containers::Point SpikeUI::Controls::Button::RelativePixelDelta(SpikeUI::Containers::Point const & relativePosition)
{
	return Place.RelativeToAbsolute(relativePosition);
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

	if (loseFocus)
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
