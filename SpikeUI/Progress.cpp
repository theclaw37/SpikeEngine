#include "Progress.h"

SpikeUI::Controls::Progress::Progress(SpikeUI::Containers::Rectangle const & place,
	std::shared_ptr<SpikeUI::Colour> fill,
	std::shared_ptr<SpikeUI::Colour> empty,
	std::string const & id) :
	Place(place),
	FillColour(fill),
	EmptyColour(empty),
	Value(0),
	Drawable(SpikeUI::UI::Progress, id)
{
	DHit = SpikeUI::UI::HitDisable;
}

void SpikeUI::Controls::Progress::SetProgress(double value)
{
	Value = CLAMP(value, 0.0, 1.0);
}

void SpikeUI::Controls::Progress::IncreaseProgress(double value)
{
	Value = CLAMP(Value + value, 0.0, 1.0);
}

double SpikeUI::Controls::Progress::GetValueCoord() const
{
	return Place.RelativeToAbsolute({ Value, 0 }).x;
}

void SpikeUI::Controls::Progress::PointerUpdate(bool leftClickDown, bool leftClickUp)
{
}

void SpikeUI::Controls::Progress::Update()
{
}

bool SpikeUI::Controls::Progress::Contains(SpikeUI::Containers::Point const & mouse)
{
	return Place.Contains(mouse);
}

void SpikeUI::Controls::Progress::MoveByPixels(SpikeUI::Containers::Point const & pixels)
{
	Place += pixels;
}

SpikeUI::Containers::Point SpikeUI::Controls::Progress::MoveToPixels(SpikeUI::Containers::Point const & pixels)
{
	auto width = Place.Width();
	auto height = Place.Height();
	auto newPlace = SpikeUI::Containers::Rectangle(pixels.x, pixels.y, pixels.x + width, pixels.y + height);
	auto delta = newPlace.TopLeft - Place.TopLeft;
	Place = newPlace;
	return delta;
}

SpikeUI::Containers::Point SpikeUI::Controls::Progress::RelativePixelDelta(SpikeUI::Containers::Point const & relativePosition)
{
	return Place.RelativeToAbsolute(relativePosition);
}