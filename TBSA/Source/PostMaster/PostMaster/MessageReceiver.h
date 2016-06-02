#pragma once
#include <Message/RecieverTypes.h>

struct FlagPlayerDiedMessage;
struct PlayerChangedTargetMessage;
struct PlayerAddedMessage;
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
struct SetHWNDMessage;
struct EnemyDirectionChangedMessage;
struct PlayerSeenMessage;
struct PlayerDiedMessage;
struct EnemyObjectMessage;
struct FightWithEnemyMessage;

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
	virtual void RecieveMessage(const SetHWNDMessage & aMessage);
	virtual void RecieveMessage(const PlayerAddedMessage & aMessage);
	virtual void RecieveMessage(const EnemyDirectionChangedMessage & aMessage);
	virtual void RecieveMessage(const PlayerSeenMessage & aMessage);
	virtual void RecieveMessage(const PlayerDiedMessage & aMessage);
	virtual void RecieveMessage(const PlayerChangedTargetMessage & aMessage);
	virtual void RecieveMessage(const EnemyObjectMessage & aMessage);
	virtual void RecieveMessage(const FightWithEnemyMessage & aMessage);
	virtual void RecieveMessage(const FlagPlayerDiedMessage &aMessage);

	RecieverOrder myRecieverOrder;
protected:
	MessageReciever()
	{
		myRecieverOrder = RecieverOrder::eDefault;
	}
};