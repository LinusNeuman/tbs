#include "stdafx.h"
#include "MessageReceiver.h"
#include <Message/WindowRectChangedMessage.h>
#include <Message/LevelTileMetricsMessage.h>
#include <Message/SetMainCameraMessage.h>

bool MessageReciever::RecieveMessage(const WindowRectChangedMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const LevelTileMetricsMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const SetMainCameraMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const DijkstraMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const NavigationClearMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const EndTurnMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const StartUpLevelMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const GUIMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const GetStartLevelMessage & aMessage)
{
	return true;

}

bool MessageReciever::RecieveMessage(const ColliderMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const PlayerPositionChangedMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const PlayerObjectMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const SetHWNDMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const PlayerAddedMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const EnemyPositionChangedMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const PlayerSeenMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const PlayerDiedMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const EnemyObjectMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const FightWithEnemyMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const FlagPlayerDiedMessage &aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const GoalReachedMessage& aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const PlayerCanPeekMessage& aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const FlagGoalReachedMessage& aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const MouseButtonDownMessage& aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const MouseButtonPressedMessage& aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const MouseButtonReleasedMessage&aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const MouseInputClearMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const PlayerIDMessage & aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const PlayerAPChangedMessage& aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const SetTargetResolutionMessage& aMessage)
{
	return true;
}

bool MessageReciever::RecieveMessage(const LogTextMessage& aMessage)
{
	return true;
}