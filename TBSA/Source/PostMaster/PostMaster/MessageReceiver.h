#pragma once
struct StartUpLevelMessage;
struct NavigationClearMessage;
struct WindowRectChangedMessage;
struct LevelTileMetricsMessage;
struct SetMainCameraMessage;
struct DijkstraMessage;
struct EndTurnMessage;
struct GUIMessage;
struct GetStartLevelMessage;

class MessageReciever
{
public:
	virtual ~MessageReciever()
	{}

	virtual void RecieveMessage(const WindowRectChangedMessage & aMessage);
	virtual void RecieveMessage(const LevelTileMetricsMessage & aMessage);
	virtual void RecieveMessage(const SetMainCameraMessage & aMessage);
	virtual void RecieveMessage(const DijkstraMessage & aMessage);
	virtual void RecieveMessage(const NavigationClearMessage & aMessage);
	virtual void RecieveMessage(const EndTurnMessage & aMessage);
	virtual void RecieveMessage(const StartUpLevelMessage & aMessage);
	virtual void RecieveMessage(const GUIMessage & aMessage);
	virtual void RecieveMessage(const GetStartLevelMessage & aMessage);

protected:
	MessageReciever()
	{}
};
