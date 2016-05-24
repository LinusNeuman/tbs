#pragma once
struct WindowRectChangedMessage;
struct LevelTileMetricsMessage;
struct DijkstraMessage;

class MessageReciever
{
public:
	virtual ~MessageReciever()
	{}

	virtual void RecieveMessage(const WindowRectChangedMessage & aMessage);
	virtual void RecieveMessage(const LevelTileMetricsMessage & aMessage);
	virtual void RecieveMessage(const DijkstraMessage & aMessage);

protected:
	MessageReciever()
	{}
};
