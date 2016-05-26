// Author:   Hampus Huledal
// CreationDate: 23/05/2016
#pragma once
#include "BaseMessage.h"
#include "RecieverTypes.h"
#include <CU/Vectors/Vector.h>
#pragma warning  (push)
#pragma warning(disable : 4512)
struct DijkstraMessage : BaseMessage
{
	DijkstraMessage(const RecieverTypes aReceiverType, const CommonUtilities::Vector2ui & aPosition, const int aDistance) :
		BaseMessage(aReceiverType),
		myPosition(aPosition),
		myDistance(aDistance)
	{}

	const CommonUtilities::Vector2ui myPosition;
	const int myDistance;
};
#pragma warning (pop)