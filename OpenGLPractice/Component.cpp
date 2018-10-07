#include "Component.h"
#include <windows.h>
#include "Logging.h"

core::Component::Component()
{
	HRESULT result = CoCreateGuid(&unique_id_);
	DEBUG_IF(!SUCCEEDED(result),
		LOG_ERR("Component was unable to allocate a unique ID! Error code " << result));
}
