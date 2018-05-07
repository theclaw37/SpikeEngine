#pragma once

#include "Renderer.h"
#include "SpikeUtils.h"

namespace SpikeRenderer
{
	namespace DirectX
	{
		struct DX2DWriteFactory : public SpikeUtils::_SpikeEngineResource<DX2DWriteFactory>
		{
			IDWriteFactory1* WriteFactory;

			DX2DWriteFactory() : DX2DWriteFactory(nullptr)
			{}

			DX2DWriteFactory(IDWriteFactory1* WriteFactory) : WriteFactory(WriteFactory)
			{}

			DX2DWriteFactory(DX2DWriteFactory && other)
			{
				WriteFactory = other.WriteFactory;
				other.WriteFactory = nullptr;
			}

			bool operator==(DX2DWriteFactory const & other) const
			{
				return (other.WriteFactory == WriteFactory);
			}

			IDWriteFactory1 * operator->()
			{
				return WriteFactory;
			}

			~DX2DWriteFactory()
			{
				if (WriteFactory)
				{
					WriteFactory->Release();
				}
			}
		};
	}
}

namespace std
{
	template <>
	struct hash<SpikeRenderer::DirectX::DX2DWriteFactory>
	{
		size_t operator()(SpikeRenderer::DirectX::DX2DWriteFactory const & ref) const
		{
			return SpikeUtils::Hashes::HashToSizeT(ref.WriteFactory);
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeRenderer::DirectX::DX2DWriteFactory>>
	{
		size_t operator()(std::shared_ptr<SpikeRenderer::DirectX::DX2DWriteFactory> const & ref) const
		{
			return hash<SpikeRenderer::DirectX::DX2DWriteFactory>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeRenderer::DirectX::DX2DWriteFactory>>
	{
		bool operator()(std::shared_ptr<SpikeRenderer::DirectX::DX2DWriteFactory> const & lhs,
			std::shared_ptr<SpikeRenderer::DirectX::DX2DWriteFactory> const & rhs) const
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