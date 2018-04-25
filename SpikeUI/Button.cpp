#include "Button.h"

SpikeUI::Controls::Button::Button(SpikeUI::Containers::Rectangle const & place,
	SpikeUI::Colour::Colour const & colour,
	std::string const & id) :
	Place(place),
	Colour(colour),
	Drawable(SpikeUI::UI::Button, id)
{
	DHit = SpikeUI::UI::HitEnable;
}

void SpikeUI::Controls::Button::PointerUpdate(bool lButtonDown, 
	bool lButtonUp,
	bool rButtonDown,
	bool rButtonUp)
{
	if (lButtonDown && this->lButtonDown)
	{
		this->lButtonDown(*this);
	}
	if (lButtonUp && this->lButtonUp)
	{
		this->lButtonUp(*this);
	}
	if (rButtonDown && this->rButtonDown)
	{
		this->rButtonDown(*this);
	}
	if (rButtonUp && this->rButtonUp)
	{
		this->rButtonUp(*this);
	}
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

void SpikeUI::Controls::Button::HoverIn()
{
	Drawable::HoverIn();

	if (hoverIn)
		hoverIn(*this);
}

void SpikeUI::Controls::Button::HoverOut()
{
	Drawable::HoverOut();

	if (hoverOut)
		hoverOut(*this);
}