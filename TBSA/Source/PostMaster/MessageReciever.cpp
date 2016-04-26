#include "MessageReciever.h"
#include "SingletonPostMaster.h"

MessageReciever::~MessageReciever()
{
	if (SingletonPostMaster::CheckIfExists() == true)
	{
		SingletonPostMaster::RemoveReciever(*this);
	}
}