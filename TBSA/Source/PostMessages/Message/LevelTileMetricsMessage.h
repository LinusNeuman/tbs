#pragma once
#include "BaseMessage.h"
#include <CU/Vectors/vector2.h>
#include <CU/NameSpaceAliases.h>

#pragma warning  (push)
#pragma warning(disable : 4512)
struct LevelTileMetricsMessage : public BaseMessage
{
	LevelTileMetricsMessage(const RecieverTypes aReceiverType, const CU::Vector2ui & aLevelWidthAndHeight) :
		BaseMessage(aReceiverType),
		myWidthHeight(aLevelWidthAndHeight)
	{}

	const CU::Vector2ui myWidthHeight;
};
#pragma warning (pop)