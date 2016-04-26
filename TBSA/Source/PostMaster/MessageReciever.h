#pragma once

struct Message;

class MessageReciever
{
public:
	virtual ~MessageReciever();

	virtual void RecieveMessage(const Message & aMessageToRecieve) = 0;

protected:
	MessageReciever()
	{}
};
