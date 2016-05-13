#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/vector2.h>
#include <CU/NameSpaceAliases.h>

struct LevelTileMetricsMessage : public BaseMessage
{
	LevelTileMetricsMessage(const RecieverTypes aReceiverType, const CU::Vector2f & aLevelWidthAndHeight) :
		BaseMessage(aReceiverType),
		myWidthHeight(aLevelWidthAndHeight)
	{}

	const CU::Vector2f myWidthHeight;
};