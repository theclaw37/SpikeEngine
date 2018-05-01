#pragma once

#include <memory>
#include <unordered_map>

namespace SpikeUtils
{
	template <typename TFrom, typename TTo>
	class ResourceMapping
	{
	public:
		static std::shared_ptr<TFrom> RegisterResource(
			std::shared_ptr<TFrom> from,
			std::shared_ptr<TTo> to)
		{
			auto result = _RTRMap.insert({ from, to });
			return (*(result.first)).first;
		}

		static std::shared_ptr<TTo> const RetrieveResource(
			std::shared_ptr<TFrom> from)
		{
			auto result = _RTRMap.find(from);
			if (result != _RTRMap.end())
			{
				return (*result).second;
			}

			return nullptr;
		}
	private:
		static std::unordered_map<std::shared_ptr<TFrom>, std::shared_ptr<TTo>> _RTRMap;
	};

	template <typename TFrom, typename TTo>
	std::unordered_map<std::shared_ptr<TFrom>, std::shared_ptr<TTo>> ResourceMapping<TFrom, TTo>::_RTRMap;
}