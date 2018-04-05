#include "Label.h"

SpikeUI::Controls::Label::Label(SpikeUI::Containers::Rectangle const & place, 
	SpikeUI::Containers::Font const & font, 
	SpikeUI::Colour::Colour const & colour) : 
		Place(place), 
		Font(font), 
		Colour(colour),
		Drawable(SpikeUI::UI::Label)
{
	DHit = SpikeUI::UI::HitDisable;
}

void SpikeUI::Controls::Label::PointerUpdate(bool lButtonDown,
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

void SpikeUI::Controls::Label::HoverIn()
{
	Drawable::HoverIn();
	
	if (hoverIn)
		hoverIn(*this);
}

void SpikeUI::Controls::Label::HoverOut()
{
	Drawable::HoverOut();

	if (hoverOut)
		hoverOut(*this);
}
