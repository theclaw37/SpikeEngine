#include "Label.h"

SpikeUI::Controls::Label::Label(SpikeUI::Containers::Rectangle const & place, 
	SpikeUI::Containers::Font const & font, 
	SpikeUI::Colour::Colour const & colour) : 
		Place(place), 
		Font(font), 
		Colour(colour),
		Drawable(SpikeUI::UI::DrawableType::Label)
{
	DHit = SpikeUI::UI::DrawableHit::Disable;
}

void SpikeUI::Controls::Label::MouseUpdate(bool leftClickDown, bool leftClickUp)
{
	if (leftClickDown)
		LeftClickDown();
	else if (leftClickUp)
		LeftClickUp();
}

void SpikeUI::Controls::Label::KeyboardUpdate(SpikeUI::Containers::Key const & key)
{
	if (receiveKey)
		receiveKey(*this, key);
}

void SpikeUI::Controls::Label::Update()
{
}

bool SpikeUI::Controls::Label::Contains(SpikeUI::Containers::Point const & mouse)
{
	return Place.Contains(mouse);
}

void SpikeUI::Controls::Label::MoveByPixels(SpikeUI::Containers::Point const & pixels)
{
	Place += pixels;
}

SpikeUI::Containers::Point SpikeUI::Controls::Label::MoveToPixels(SpikeUI::Containers::Point const & pixels)
{
	auto width = Place.Width();
	auto height = Place.Height();
	auto newPlace = SpikeUI::Containers::Rectangle(pixels.x, pixels.y, pixels.x + width, pixels.y + height);
	auto delta = newPlace.TopLeft - Place.TopLeft;
	Place = newPlace;
	return delta;
}

SpikeUI::Containers::Point SpikeUI::Controls::Label::RelativePixelDelta(SpikeUI::Containers::Point const & relativePosition)
{
	return Place.RelativeToAbsolute(relativePosition);
}

void SpikeUI::Controls::Label::ReceiveFocus()
{
	DState = SpikeUI::UI::DrawableState::Hover;
	
	if (receiveFocus)
		receiveFocus(*this);
}

void SpikeUI::Controls::Label::LoseFocus()
{
	DState = SpikeUI::UI::DrawableState::Default;

	if (loseFocus)
		loseFocus(*this);
}

void SpikeUI::Controls::Label::LeftClickDown()
{
	if (lClickDown)
		lClickDown(*this);
}

void SpikeUI::Controls::Label::LeftClickUp()
{
	if (lClickUp)
		lClickUp(*this);
}
