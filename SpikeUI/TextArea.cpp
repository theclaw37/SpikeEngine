#include "TextArea.h"

SpikeUI::Text::TextArea::TextArea(SpikeUI::Containers::Rectangle const & place, 
	SpikeUI::Text::Font const & font, 
	SpikeUI::Colour::Colour const & colour) : 
		Place(place), 
		Font(font), 
		Colour(colour),
		Drawable(SpikeUI::UI::DrawableType::TextArea)
{
}
