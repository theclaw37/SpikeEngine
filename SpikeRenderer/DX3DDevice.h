#pragma once

#include "Renderer.h"
#include "SpikeUtils.h"

namespace SpikeRenderer
{
	namespace DirectX
	{
		struct DX3DDevice : public SpikeUtils::_SpikeEngineResource<DX3DDevice>
		{
			ID3D11Device* Device;

			DX3DDevice() : DX3DDevice(nullptr)
			{}

			DX3DDevice(ID3D11Device* Device) : Device(Device)
			{}

			DX3DDevice(DX3DDevice && other)
			{
				Device = other.Device;
				other.Device = nullptr;
			}

			bool operator==(DX3DDevice const & other) const
			{
				return (other.Device == Device);
			}

			ID3D11Device * operator->()
			{
				return Device;
			}

			~DX3DDevice()
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
	struct hash<SpikeRenderer::DirectX::DX3DDevice>
	{
		size_t operator()(SpikeRenderer::DirectX::DX3DDevice const & ref) const
		{
			return SpikeUtils::Hashes::HashToSizeT(ref.Device);
		}
	};


	template <>
	struct hash<std::shared_ptr<SpikeRenderer::DirectX::DX3DDevice>>
	{
		size_t operator()(std::shared_ptr<SpikeRenderer::DirectX::DX3DDevice> const & ref) const
		{
			return hash<SpikeRenderer::DirectX::DX3DDevice>()(*ref);
		}
	};

	template <>
	struct equal_to<std::shared_ptr<SpikeRenderer::DirectX::DX3DDevice>>
	{
		bool operator()(std::shared_ptr<SpikeRenderer::DirectX::DX3DDevice> const & lhs,
			std::shared_ptr<SpikeRenderer::DirectX::DX3DDevice> const & rhs) const
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