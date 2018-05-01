#pragma once

#include <string>

namespace SpikeUI
{
	namespace Containers
	{
		struct Font : public SpikeUtils::_SpikeEngineResource<Font>
		{
			std::wstring FontFamily;
			unsigned int Size;

			Font(std::wstring const & family, unsigned int size) : FontFamily(family), Size(size)
			{}

			bool operator==(Font const & other) const
			{
				return (FontFamily == other.FontFamily && Size == other.Size);
			}
		};
	}
}


namespace std
{
	template <>
	struct hash<SpikeUI::Containers::Font>
	{
		size_t operator()(SpikeUI::Containers::Font const & ref) const
		{
			return hash<std::wstring>()(ref.FontFamily + to_wstring(ref.Size));
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeUI::Containers::Font>>
	{
		size_t operator()(std::shared_ptr<SpikeUI::Containers::Font> const & ref) const
		{
			return hash<SpikeUI::Containers::Font>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeUI::Containers::Font>>
	{
		bool operator()(std::shared_ptr<SpikeUI::Containers::Font> const & lhs,
			std::shared_ptr<SpikeUI::Containers::Font> const & rhs) const
		{
			if (lhs == rhs)
			{
				return true;
			}
			else
			{
				return *lhs == *rhs;
			}
		}
	};
}