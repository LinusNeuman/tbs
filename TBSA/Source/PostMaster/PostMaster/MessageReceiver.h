#pragma once
#include <Message/RecieverTypes.h>

struct FlagGoalReachedMessage;
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
struct GoalReachedMessage;

class MessageReciever
{
public:
	virtual ~MessageReciever()
	{}

	virtual bool RecieveMessage(const WindowRectChangedMessage & aMessage);
	virtual bool RecieveMessage(const LevelTileMetricsMessage & aMessage);
	virtual bool RecieveMessage(const SetMainCameraMessage & aMessage);
	virtual bool RecieveMessage(const DijkstraMessage & aMessage);
	virtual bool RecieveMessage(const NavigationClearMessage & aMessage);
	virtual bool RecieveMessage(const EndTurnMessage & aMessage);
	virtual bool RecieveMessage(const StartUpLevelMessage & aMessage);
	virtual bool RecieveMessage(const GUIMessage & aMessage);
	virtual bool RecieveMessage(const GetStartLevelMessage & aMessage);
	virtual bool RecieveMessage(const ColliderMessage & aMessage);
	virtual bool RecieveMessage(const ActorPositionChangedMessage & aMessage);
	virtual bool RecieveMessage(const PlayerObjectMessage & aMessage);
	virtual bool RecieveMessage(const SetHWNDMessage & aMessage);
	virtual bool RecieveMessage(const PlayerAddedMessage & aMessage);
	virtual bool RecieveMessage(const EnemyDirectionChangedMessage & aMessage);
	virtual bool RecieveMessage(const PlayerSeenMessage & aMessage);
	virtual bool RecieveMessage(const PlayerDiedMessage & aMessage);
	virtual bool RecieveMessage(const PlayerChangedTargetMessage & aMessage);
	virtual bool RecieveMessage(const EnemyObjectMessage & aMessage);
	virtual bool RecieveMessage(const FightWithEnemyMessage & aMessage);
	virtual bool RecieveMessage(const FlagPlayerDiedMessage &aMessage);
	virtual bool RecieveMessage(const FlagGoalReachedMessage& aMessage);
	virtual bool RecieveMessage(const GoalReachedMessage& aMessage);

	RecieverOrder myRecieverOrder;
protected:
	MessageReciever()
	{
		myRecieverOrder = RecieverOrder::eDefault;
	}
};
