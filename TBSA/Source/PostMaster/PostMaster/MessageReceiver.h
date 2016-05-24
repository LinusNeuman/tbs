#pragma once
struct WindowRectChangedMessage;
struct LevelTileMetricsMessage;
struct SetMainCameraMessage;

class MessageReciever
{
public:
	virtual ~MessageReciever()
	{}

	virtual void RecieveMessage(const WindowRectChangedMessage & aMessage);
	virtual void RecieveMessage(const LevelTileMetricsMessage & aMessage);
	virtual void RecieveMessage(const SetMainCameraMessage & aMessage);

protected:
	MessageReciever()
	{}
};
