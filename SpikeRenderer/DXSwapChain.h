#pragma once

#include "Renderer.h"
#include "SpikeUtils.h"

namespace SpikeRenderer
{
	namespace DirectX
	{
		struct DXSwapChain : public SpikeUtils::_SpikeEngineResource<DXSwapChain>
		{
			IDXGISwapChain* SwapChain;

			DXSwapChain() : DXSwapChain(nullptr)
			{}

			DXSwapChain(IDXGISwapChain* swapChain) : SwapChain(swapChain)
			{}

			DXSwapChain(DXSwapChain && other)
			{
				SwapChain = other.SwapChain;
				other.SwapChain = nullptr;
			}

			bool operator==(DXSwapChain const & other) const
			{
				return (other.SwapChain == SwapChain);
			}

			IDXGISwapChain * operator->()
			{
				return SwapChain;
			}

			~DXSwapChain()
			{
				if (SwapChain)
				{
					SwapChain->Release();
				}
			}
		};
	}
}

namespace std
{
	template <>
	struct hash<SpikeRenderer::DirectX::DXSwapChain>
	{
		size_t operator()(SpikeRenderer::DirectX::DXSwapChain const & ref) const
		{
			return SpikeUtils::Hashes::HashToSizeT(ref.SwapChain);
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeRenderer::DirectX::DXSwapChain>>
	{
		size_t operator()(std::shared_ptr<SpikeRenderer::DirectX::DXSwapChain> const & ref) const
		{
			return hash<SpikeRenderer::DirectX::DXSwapChain>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeRenderer::DirectX::DXSwapChain>>
	{
		bool operator()(std::shared_ptr<SpikeRenderer::DirectX::DXSwapChain> const & lhs,
			std::shared_ptr<SpikeRenderer::DirectX::DXSwapChain> const & rhs) const
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