#pragma once
struct ActorPositionChangedMessage;
struct StartUpLevelMessage;
struct NavigationClearMessage;
struct WindowRectChangedMessage;
struct LevelTileMetricsMessage;
struct SetMainCameraMessage;
struct DijkstraMessage;
struct EndTurnMessage;
struct GUIMessage;
struct GetStartLevelMessage;
struct ColliderMessage;
struct PlayerObjectMessage;

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
	virtual void RecieveMessage(const ColliderMessage & aMessage);
	virtual void RecieveMessage(const ActorPositionChangedMessage & aMessage);
	virtual void RecieveMessage(const PlayerObjectMessage & aMessage);

protected:
	MessageReciever()
	{}
};
