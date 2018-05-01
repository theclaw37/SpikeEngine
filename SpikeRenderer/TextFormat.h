#pragma once

#include <d2d1.h>
#include "SpikeUtils.h"

namespace SpikeRenderer
{
	namespace DirectX
	{
		struct TextFormat : public SpikeUtils::_SpikeEngineResource<TextFormat>
		{
			IDWriteTextFormat* TextFormatPointer;

			TextFormat(IDWriteTextFormat* textFormat) : TextFormatPointer(textFormat)
			{}

			TextFormat(TextFormat && other)
			{
				TextFormatPointer = other.TextFormatPointer;
				other.TextFormatPointer = nullptr;
			}

			bool operator==(TextFormat const & other) const
			{
				return (other.TextFormatPointer == TextFormatPointer);
			}

			~TextFormat()
			{
				if (TextFormatPointer)
				{
					TextFormatPointer->Release();
				}
			}
		};
	}
}

namespace std
{
	template <>
	struct hash<SpikeRenderer::DirectX::TextFormat>
	{
		size_t operator()(SpikeRenderer::DirectX::TextFormat const & ref) const
		{
			return SpikeUtils::Hashes::HashToSizeT(ref.TextFormatPointer);
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeRenderer::DirectX::TextFormat>>
	{
		size_t operator()(std::shared_ptr<SpikeRenderer::DirectX::TextFormat> const & ref) const
		{
			return hash<SpikeRenderer::DirectX::TextFormat>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeRenderer::DirectX::TextFormat>>
	{
		bool operator()(std::shared_ptr<SpikeRenderer::DirectX::TextFormat> const & lhs,
			std::shared_ptr<SpikeRenderer::DirectX::TextFormat> const & rhs) const
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