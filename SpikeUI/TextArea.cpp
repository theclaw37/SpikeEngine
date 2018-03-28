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

void SpikeUI::Controls::TextArea::KeyboardUpdate(SpikeUI::Containers::Key const & key)
{
	if (receiveKey)
		receiveKey(*this, key);
}

void SpikeUI::Controls::TextArea::Update()
{
}

bool SpikeUI::Controls::TextArea::Contains(SpikeUI::Containers::Point const & mouse)
{
	return Place.Contains(mouse);
}

void SpikeUI::Controls::TextArea::MoveByPixels(SpikeUI::Containers::Point const & pixels)
{
	Place += pixels;
}

SpikeUI::Containers::Point SpikeUI::Controls::TextArea::MoveToPixels(SpikeUI::Containers::Point const & pixels)
{
	auto width = Place.Width();
	auto height = Place.Height();
	auto newPlace = SpikeUI::Containers::Rectangle(pixels.x, pixels.y, pixels.x + width, pixels.y + height);
	auto delta = newPlace.TopLeft - Place.TopLeft;
	Place = newPlace;
	return delta;
}

SpikeUI::Containers::Point SpikeUI::Controls::TextArea::RelativePixelDelta(SpikeUI::Containers::Point const & relativePosition)
{
	return Place.RelativeToAbsolute(relativePosition) - Place.TopLeft;
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
