#pragma once

#include <Message/TestPosition.h>

class MessageReciever
{
public:
	virtual ~MessageReciever()
	{}

	virtual void RecieveMessage(const TestPositionMessage aMessage);

protected:
	MessageReciever()
	{}
};

inline void MessageReciever::RecieveMessage(const TestPositionMessage aMessage)
{
}
