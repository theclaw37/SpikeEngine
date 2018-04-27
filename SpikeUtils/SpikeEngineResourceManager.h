#pragma once

#include <memory>

namespace SpikeUtils
{
	class SpikeResourceManager
	{
	public:
		template <typename ResourceType>
		static std::shared_ptr<ResourceType> RegisterResource(ResourceType & resource)
		{
			auto pointer = std::make_shared<ResourceType>(resource);
			if (pointer)
			{
				auto result = _SpikeEngineResource<ResourceType>::_Items.insert(pointer);
				if (!result.second)
				{
					pointer = *(result.first);
				}
			}

			return pointer;
		}
	};
}