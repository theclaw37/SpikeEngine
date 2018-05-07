#pragma once

#include "Renderer.h"
#include "SpikeUtils.h"

namespace SpikeRenderer
{
	namespace DirectX
	{
		struct DX3DDeviceContext : public SpikeUtils::_SpikeEngineResource<DX3DDeviceContext>
		{
			ID3D11DeviceContext* Device;

			DX3DDeviceContext() : DX3DDeviceContext(nullptr)
			{}

			DX3DDeviceContext(ID3D11DeviceContext* Device) : Device(Device)
			{}

			DX3DDeviceContext(DX3DDeviceContext && other)
			{
				Device = other.Device;
				other.Device = nullptr;
			}

			bool operator==(DX3DDeviceContext const & other) const
			{
				return (other.Device == Device);
			}

			ID3D11DeviceContext * operator->()
			{
				return Device;
			}

			~DX3DDeviceContext()
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
	struct hash<SpikeRenderer::DirectX::DX3DDeviceContext>
	{
		size_t operator()(SpikeRenderer::DirectX::DX3DDeviceContext const & ref) const
		{
			return SpikeUtils::Hashes::HashToSizeT(ref.Device);
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeRenderer::DirectX::DX3DDeviceContext>>
	{
		size_t operator()(std::shared_ptr<SpikeRenderer::DirectX::DX3DDeviceContext> const & ref) const
		{
			return hash<SpikeRenderer::DirectX::DX3DDeviceContext>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeRenderer::DirectX::DX3DDeviceContext>>
	{
		bool operator()(std::shared_ptr<SpikeRenderer::DirectX::DX3DDeviceContext> const & lhs,
			std::shared_ptr<SpikeRenderer::DirectX::DX3DDeviceContext> const & rhs) const
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