#include "_SpikeEngineObject.h"

SpikeUtils::_SpikeEngineObject::_SpikeEngineObject(std::string const & id) :
	_SpikeRef(SpikeUtils::GUID::Generate()),
	_SpikeId(id)
{

}
