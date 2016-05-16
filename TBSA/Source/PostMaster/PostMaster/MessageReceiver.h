#pragma once
struct WindowRectChangedMessage;
struct LevelTileMetricsMessage;

class MessageReciever
{
public:
	virtual ~MessageReciever()
	{}

	virtual void RecieveMessage(const WindowRectChangedMessage & aMessage);
	virtual void RecieveMessage(const LevelTileMetricsMessage & aMessage);

protected:
	MessageReciever()
	{}
};
