#include "GUID.h"

#ifdef _WIN32
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")
#else

#endif

bool SpikeUtils::GUID::operator==(GUID const & other) const
{
	return value == other.value;
}

SpikeUtils::GUID::operator std::string() const
{
	return value;
}

SpikeUtils::GUID SpikeUtils::GUID::Generate()
{
#ifdef _WIN32
	UUID uuid;
	UuidCreate(&uuid);

	unsigned char * str;
	UuidToStringA(&uuid, &str);

	std::string s((char*)str);
	SpikeUtils::GUID guid(s);

	RpcStringFreeA(&str);
#else

#endif
	return guid;
}

SpikeUtils::GUID SpikeUtils::GUID::Parse(std::string const & input)
{
	UUID uuid;
	if (UuidFromStringA((RPC_CSTR)input.c_str(), &uuid) == RPC_S_OK)
	{
		return SpikeUtils::GUID(input);
	}

	return nullptr;
}

std::string const & SpikeUtils::GUID::Value() const
{
	return value;
}
