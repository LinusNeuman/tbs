#pragma once

#include <Message/TestPosition.h>

class MessageReciever
{
public:
	virtual ~MessageReciever()
	{}

	virtual void RecieveMessage(const TestPositionMessage aMessage) = 0;

protected:
	MessageReciever()
	{}
};