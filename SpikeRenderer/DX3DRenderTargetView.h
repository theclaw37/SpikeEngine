#pragma once

#include "Renderer.h"
#include "SpikeUtils.h"

namespace SpikeRenderer
{
	namespace DirectX
	{
		struct DX3DRenderTargetView : public SpikeUtils::_SpikeEngineResource<DX3DRenderTargetView>
		{
			ID3D11RenderTargetView* Device;

			DX3DRenderTargetView() : DX3DRenderTargetView(nullptr)
			{}

			DX3DRenderTargetView(ID3D11RenderTargetView* Device) : Device(Device)
			{}

			DX3DRenderTargetView(DX3DRenderTargetView && other)
			{
				Device = other.Device;
				other.Device = nullptr;
			}

			bool operator==(DX3DRenderTargetView const & other) const
			{
				return (other.Device == Device);
			}

			ID3D11RenderTargetView * operator->()
			{
				return Device;
			}

			~DX3DRenderTargetView()
			{
				if (Device)
				{
					Device->Release();
				}
			}
		};
	}
}

namespace std
{
	template <>
	struct hash<SpikeRenderer::DirectX::DX3DRenderTargetView>
	{
		size_t operator()(SpikeRenderer::DirectX::DX3DRenderTargetView const & ref) const
		{
			return SpikeUtils::Hashes::HashToSizeT(ref.Device);
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeRenderer::DirectX::DX3DRenderTargetView>>
	{
		size_t operator()(std::shared_ptr<SpikeRenderer::DirectX::DX3DRenderTargetView> const & ref) const
		{
			return hash<SpikeRenderer::DirectX::DX3DRenderTargetView>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeRenderer::DirectX::DX3DRenderTargetView>>
	{
		bool operator()(std::shared_ptr<SpikeRenderer::DirectX::DX3DRenderTargetView> const & lhs,
			std::shared_ptr<SpikeRenderer::DirectX::DX3DRenderTargetView> const & rhs) const
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