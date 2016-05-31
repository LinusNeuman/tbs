#pragma once

#include "Message/BaseMessage.h"

class GameObjectCollider;

#pragma warning  (push)
#pragma warning(disable : 4512)
struct ColliderMessage : public BaseMessage
{
	ColliderMessage(const RecieverTypes aRecieverType, const GameObjectCollider & aCollider) 
		: BaseMessage(aRecieverType),
		myCollider(aCollider)
	{
	}

	const GameObjectCollider & myCollider;
};
#pragma warning (pop)