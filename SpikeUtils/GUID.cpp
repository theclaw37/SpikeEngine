#include "GUID.h"

#ifdef _WIN32
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")
#else

#endif

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

std::string const & SpikeUtils::GUID::Value() const
{
	return value;
}
