#include "TextArea.h"

SpikeUI::Controls::TextArea::TextArea(
	SpikeUI::Containers::Rectangle const & place,
	SpikeUI::Containers::Font const & font,
	SpikeUI::Colour const & textColour,
	SpikeUI::Colour const & backgroundColour,
	std::string const & id) :
	Place(place),
	Font(font),
	TextColour(textColour),
	BackgroundColour(backgroundColour),
	Drawable(SpikeUI::UI::TextArea, id)
{
	DHit = SpikeUI::UI::HitEnable;
}

void SpikeUI::Controls::TextArea::PointerUpdate(bool, bool, bool, bool)
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

void SpikeUI::Controls::TextArea::KeyInput(SpikeUI::Containers::Key const & key)
{
	if (key.IsCharacter())
	{
		Text += key.Character;
	}
	else
	{
		switch (key.CharacterControl)
		{
			case Containers::Backspace:
			{
				if (!Text.empty())
					Text.pop_back();
			} break;
			case Containers::Enter:
			{
				Text += '\n';
			} break;
			case Containers::Space:
			{
				Text += ' ';
			} break;
		}
	}
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
	return Place.RelativeToAbsolute(relativePosition);
}

void SpikeUI::Controls::TextArea::HoverIn()
{
	Drawable::HoverIn();

	if (hoverIn)
		hoverIn(*this);
}

void SpikeUI::Controls::TextArea::HoverOut()
{
	Drawable::HoverOut();

	if (hoverOut)
		hoverOut(*this);
}

void SpikeUI::Controls::TextArea::Focus()
{
	Drawable::Focus();
}

void SpikeUI::Controls::TextArea::Unfocus()
{
	Drawable::Unfocus();
}
