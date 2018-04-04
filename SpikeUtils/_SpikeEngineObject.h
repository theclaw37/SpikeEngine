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
		_SpikeEngineObject();
		const std::string & _SpikeEngineId() const
		{
			return _SpikeRef.Value();
		}
		virtual ~_SpikeEngineObject() = 0;
	private:
		SpikeUtils::GUID _SpikeRef;
	};

	inline _SpikeEngineObject::~_SpikeEngineObject() = default;
}
