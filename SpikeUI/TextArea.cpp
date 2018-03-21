#include "TextArea.h"

#include <Windows.h>

SpikeUI::Text::TextArea::TextArea(SpikeUI::Containers::Rectangle const & place, 
	SpikeUI::Text::Font const & font, 
	SpikeUI::Colour::Colour const & colour) : 
		Place(place), 
		Font(font), 
		Colour(colour),
		Drawable(SpikeUI::UI::DrawableType::TextArea)
{
}

bool SpikeUI::Text::TextArea::HandleMouse(SpikeUI::Containers::Point coord, bool leftClickDown, bool leftClickUp)
{
	auto hit = (coord.x >= Place.TopLeft.x)
		&& (coord.x <= Place.BottomRight.x)
		&& (coord.y >= Place.TopLeft.y)
		&& (coord.y <= Place.BottomRight.y);

	if (hit)
	{
		if (leftClickDown)
			LeftClickDown();
		else if (leftClickUp)
			LeftClickUp();
	}

	return hit;
}

void SpikeUI::Text::TextArea::ReceiveFocus()
{
	Colour = SpikeUI::Colour::Colour(0.0, 0.0, 0.0);
	State = SpikeUI::UI::DrawableState::Hover;
}

void SpikeUI::Text::TextArea::LoseFocus()
{
	Colour = SpikeUI::Colour::Colour(1.0, 1.0, 1.0);
	State = SpikeUI::UI::DrawableState::Default;
}

void SpikeUI::Text::TextArea::LeftClickDown()
{
	Beep(440, 300);
}

void SpikeUI::Text::TextArea::LeftClickUp()
{
	Beep(880, 300);
}
