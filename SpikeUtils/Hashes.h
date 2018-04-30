#pragma once

#include "MurmurHash3.h"

namespace SpikeUtils
{
	namespace Hashes
	{
		template <typename T>
		size_t HashToSizeT(T const & ref)
		{
			uint64_t seed = 1;
			uint64_t hash[2];
			MurmurHash3_x64_128(&ref, sizeof(T), seed, hash);
			return *(size_t *)hash;
		}
	}
}