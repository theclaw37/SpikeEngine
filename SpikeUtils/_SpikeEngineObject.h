#pragma once

#ifdef DLL_SPIKEUTILS
#define SPIKEUTILS_EXPORT __declspec(dllexport)
#else
#define SPIKEUTILS_EXPORT __declspec(dllimport)
#endif

#include "GUID.h"

namespace SpikeUtils
{
	class SPIKEUTILS_EXPORT _SpikeEngineObject
	{
	public:
		_SpikeEngineObject(std::string const &);
		
		const SpikeUtils::GUID & _SpikeEngineId() const
		{
			return _SpikeRef;
		}

		const std::string & _SpikeObjectId() const
		{
			return _SpikeId;
		}

		virtual ~_SpikeEngineObject() = default;
	private:
		SpikeUtils::GUID _SpikeRef;
		std::string _SpikeId;
	};
}
