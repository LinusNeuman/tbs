#pragma once

#include <Message/TestPosition.h>
#include <Message/WindowRectChangedMessage.h>

class MessageReciever
{
public:
	virtual ~MessageReciever()
	{}

	virtual void RecieveMessage(const TestPositionMessage aMessage);
	virtual void RecieveMessage(const WindowRectChangedMessage aMessage);

protected:
	MessageReciever()
	{}
};
