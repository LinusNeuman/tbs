#pragma once
#include <Message/RecieverTypes.h>

struct EnemyDirectionChangedMessage;
struct FlagGoalReachedMessage;
struct FlagPlayerDiedMessage;
struct PlayerAddedMessage;
struct PlayerPositionChangedMessage;
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
struct EnemyPositionChangedMessage;
struct PlayerSeenMessage;
struct PlayerDiedMessage;
struct EnemyObjectMessage;
struct FightWithEnemyMessage;
struct GoalReachedMessage;
struct PlayerCanPeekMessage;
struct MouseButtonDownMessage;
struct MouseButtonReleasedMessage;
struct MouseButtonPressedMessage;
struct MouseInputClearMessage;
struct PlayerIDMessage;
struct PlayerAPChangedMessage;
struct SetTargetResolutionMessage;
struct DialogTextMessage;
struct ClearLogMessage;
struct ScrollLogUpMessage;
struct ScrollLogDownMessage;
struct LevelChangeMassage;

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
	virtual bool RecieveMessage(const PlayerPositionChangedMessage & aMessage);
	virtual bool RecieveMessage(const PlayerObjectMessage & aMessage);
	virtual bool RecieveMessage(const SetHWNDMessage & aMessage);
	virtual bool RecieveMessage(const PlayerAddedMessage & aMessage);
	virtual bool RecieveMessage(const EnemyPositionChangedMessage & aMessage);
	virtual bool RecieveMessage(const PlayerSeenMessage & aMessage);
	virtual bool RecieveMessage(const PlayerDiedMessage & aMessage);
	virtual bool RecieveMessage(const EnemyObjectMessage & aMessage);
	virtual bool RecieveMessage(const FightWithEnemyMessage & aMessage);
	virtual bool RecieveMessage(const FlagPlayerDiedMessage &aMessage);
	virtual bool RecieveMessage(const FlagGoalReachedMessage& aMessage);
	virtual bool RecieveMessage(const GoalReachedMessage& aMessage);
	virtual bool RecieveMessage(const PlayerCanPeekMessage& aMessage);
	virtual bool RecieveMessage(const MouseButtonDownMessage& aMessage);
	virtual bool RecieveMessage(const MouseButtonPressedMessage& aMessage);
	virtual bool RecieveMessage(const MouseButtonReleasedMessage&aMessage);
	virtual bool RecieveMessage(const MouseInputClearMessage & aMessage);
	virtual bool RecieveMessage(const PlayerIDMessage & aMessage);
	virtual bool RecieveMessage(const PlayerAPChangedMessage& aMessage);
	virtual bool RecieveMessage(const SetTargetResolutionMessage& aMessage);
	virtual bool RecieveMessage(const DialogTextMessage& aMessage);
	virtual bool RecieveMessage(const ClearLogMessage& aMessage);
	virtual bool RecieveMessage(const ScrollLogUpMessage& aMessage);
	virtual bool RecieveMessage(const ScrollLogDownMessage& aMessage);
	virtual bool RecieveMessage(const LevelChangeMassage& aMessage);
	virtual bool RecieveMessage(const EnemyDirectionChangedMessage& aMessage);

	RecieverOrder myRecieverOrder;
protected:
	MessageReciever()
	{
		myRecieverOrder = RecieverOrder::eDefault;
	}
};
