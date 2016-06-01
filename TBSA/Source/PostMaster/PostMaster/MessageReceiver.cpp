#include "stdafx.h"
#include "MessageReceiver.h"
#include <Message/WindowRectChangedMessage.h>
#include <Message/LevelTileMetricsMessage.h>
#include <Message/SetMainCameraMessage.h>

void MessageReciever::RecieveMessage(const WindowRectChangedMessage & aMessage)
{
}

void MessageReciever::RecieveMessage(const LevelTileMetricsMessage & aMessage)
{
}

void MessageReciever::RecieveMessage(const SetMainCameraMessage & aMessage)
{

}

void MessageReciever::RecieveMessage(const DijkstraMessage& aMessage)
{
}

void MessageReciever::RecieveMessage(const NavigationClearMessage& aMessage)
{
}

void MessageReciever::RecieveMessage(const EndTurnMessage& aMessage)
{
}

void MessageReciever::RecieveMessage(const StartUpLevelMessage& aMessage)
{
}

void MessageReciever::RecieveMessage(const GUIMessage& aMessage)
{
}

void MessageReciever::RecieveMessage(const GetStartLevelMessage& aMessage)
{
}

void MessageReciever::RecieveMessage(const ColliderMessage & aMessage)
{

}

void MessageReciever::RecieveMessage(const ActorPositionChangedMessage& aMessage)
{
}

void MessageReciever::RecieveMessage(const PlayerObjectMessage & aMessage)
{

}

void MessageReciever::RecieveMessage(const SetHWNDMessage & aMessage)
{

}

void MessageReciever::RecieveMessage(const PlayerAddedMessage& aMessage)
{

}

void MessageReciever::RecieveMessage(const EnemyChangedDirectionMessage & aMessage)
{

}

void MessageReciever::RecieveMessage(const PlayerChangedTargetMessage& aMessage)
{
}
