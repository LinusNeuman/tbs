#pragma once
#include "BaseMessage.h"

class ScoreCounter;

#pragma warning  (push)
#pragma warning(disable : 4512)

struct ScoreCounterMessage :public BaseMessage
{
	ScoreCounterMessage(const RecieverTypes aType, const ScoreCounter & aScoreCounter) : BaseMessage(aType), myScoreCounter(aScoreCounter)
	{
	}

	const ScoreCounter & myScoreCounter;
};

#pragma warning (pop)