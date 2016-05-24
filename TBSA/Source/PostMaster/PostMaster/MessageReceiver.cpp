#include "stdafx.h"
#include "MessageReceiver.h"
#include <Message/WindowRectChangedMessage.h>
#include <Message/LevelTileMetricsMessage.h>

void MessageReciever::RecieveMessage(const WindowRectChangedMessage & aMessage)
{
}

void MessageReciever::RecieveMessage(const LevelTileMetricsMessage & aMessage)
{
}

void MessageReciever::RecieveMessage(const DijkstraMessage& aMessage)
{
}
