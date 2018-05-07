#pragma once

#include "Renderer.h"
#include "SpikeUtils.h"

namespace SpikeRenderer
{
	namespace DirectX
	{
		struct DX2DRenderTarget : public SpikeUtils::_SpikeEngineResource<DX2DRenderTarget>
		{
			ID2D1RenderTarget* RenderTarget;

			DX2DRenderTarget() : DX2DRenderTarget(nullptr) 
			{}

			DX2DRenderTarget(ID2D1RenderTarget* RenderTarget) : RenderTarget(RenderTarget)
			{}

			DX2DRenderTarget(DX2DRenderTarget && other)
			{
				RenderTarget = other.RenderTarget;
				other.RenderTarget = nullptr;
			}

			bool operator==(DX2DRenderTarget const & other) const
			{
				return (other.RenderTarget == RenderTarget);
			}

			ID2D1RenderTarget * operator->()
			{
				return RenderTarget;
			}

			~DX2DRenderTarget()
			{
				if (RenderTarget)
				{
					RenderTarget->Release();
				}
			}
		};
	}
}

namespace std
{
	template <>
	struct hash<SpikeRenderer::DirectX::DX2DRenderTarget>
	{
		size_t operator()(SpikeRenderer::DirectX::DX2DRenderTarget const & ref) const
		{
			return SpikeUtils::Hashes::HashToSizeT(ref.RenderTarget);
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeRenderer::DirectX::DX2DRenderTarget>>
	{
		size_t operator()(std::shared_ptr<SpikeRenderer::DirectX::DX2DRenderTarget> const & ref) const
		{
			return hash<SpikeRenderer::DirectX::DX2DRenderTarget>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeRenderer::DirectX::DX2DRenderTarget>>
	{
		bool operator()(std::shared_ptr<SpikeRenderer::DirectX::DX2DRenderTarget> const & lhs,
			std::shared_ptr<SpikeRenderer::DirectX::DX2DRenderTarget> const & rhs) const
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