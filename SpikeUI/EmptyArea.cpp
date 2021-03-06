#include "EmptyArea.h"

SpikeUI::Controls::EmptyArea::EmptyArea(
	SpikeUI::Containers::Rectangle const & place, 
	std::string const & id) :
	Place(place),
	Drawable(SpikeUI::UI::EmptyArea, id)
{
	DHit = SpikeUI::UI::HitDisable;
}

bool SpikeUI::Controls::EmptyArea::Contains(SpikeUI::Containers::Point const & mouse)
{
	return Place.Contains(mouse);
}

void SpikeUI::Controls::EmptyArea::MoveByPixels(SpikeUI::Containers::Point const & pixels)
{
	Place += pixels;
}

SpikeUI::Containers::Point SpikeUI::Controls::EmptyArea::MoveToPixels(SpikeUI::Containers::Point const & pixels)
{
	auto width = Place.Width();
	auto height = Place.Height();
	auto newPlace = SpikeUI::Containers::Rectangle(pixels.x, pixels.y, pixels.x + width, pixels.y + height);
	auto delta = newPlace.TopLeft - Place.TopLeft;
	Place = newPlace;
	return delta;
}

SpikeUI::Containers::Point SpikeUI::Controls::EmptyArea::RelativePixelDelta(SpikeUI::Containers::Point const & relativePosition)
{
	return Place.RelativeToAbsolute(relativePosition);
}