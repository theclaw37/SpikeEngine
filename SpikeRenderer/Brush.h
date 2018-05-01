#pragma once

#include <d2d1.h>
#include "SpikeUtils.h"

namespace SpikeRenderer
{
	namespace DirectX
	{
		struct Brush : public SpikeUtils::_SpikeEngineResource<Brush>
		{
			ID2D1SolidColorBrush* BrushPointer;

			Brush(ID2D1SolidColorBrush* brush) : BrushPointer(brush)
			{}

			Brush(Brush && other)
			{
				BrushPointer = other.BrushPointer;
				other.BrushPointer = nullptr;
			}

			bool operator==(Brush const & other) const
			{
				return (other.BrushPointer == BrushPointer);
			}

			~Brush()
			{
				if (BrushPointer)
				{
					BrushPointer->Release();
				}
			}
		};
	}
}

namespace std
{
	template <>
	struct hash<SpikeRenderer::DirectX::Brush>
	{
		size_t operator()(SpikeRenderer::DirectX::Brush const & ref) const
		{
			return SpikeUtils::Hashes::HashToSizeT(ref.BrushPointer);
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeRenderer::DirectX::Brush>>
	{
		size_t operator()(std::shared_ptr<SpikeRenderer::DirectX::Brush> const & ref) const
		{
			return hash<SpikeRenderer::DirectX::Brush>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeRenderer::DirectX::Brush>>
	{
		bool operator()(std::shared_ptr<SpikeRenderer::DirectX::Brush> const & lhs,
			std::shared_ptr<SpikeRenderer::DirectX::Brush> const & rhs) const
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