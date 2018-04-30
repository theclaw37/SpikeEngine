#pragma once

#include "SpikeUtils.h"

namespace SpikeUI
{
	struct Colour : public SpikeUtils::_SpikeEngineResource<Colour>
	{
		double r, g, b;

		Colour(double r, double g, double b) : r(r), g(g), b(b)
		{}

		bool operator==(Colour const & other) const
		{
			return (r == other.r &&
				g == other.g &&
				b == other.b);
		}
	};
}

namespace std
{
	template <>
	struct hash<SpikeUI::Colour>
	{
		size_t operator()(SpikeUI::Colour const & ref) const
		{
			double hashObj[3] = { ref.r, ref.g, ref.b };
			return SpikeUtils::Hashes::HashToSizeT(hashObj);
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeUI::Colour>>
	{
		size_t operator()(std::shared_ptr<SpikeUI::Colour> const & ref) const
		{
			return hash<SpikeUI::Colour>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeUI::Colour>>
	{
		bool operator()(std::shared_ptr<SpikeUI::Colour> const & lhs,
			std::shared_ptr<SpikeUI::Colour> const & rhs) const
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