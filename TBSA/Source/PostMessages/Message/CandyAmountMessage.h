#pragma once

#include "Message/BaseMessage.h"

#pragma warning (push)
#pragma warning (disable : 4512)

struct CandyAmountMessage : public BaseMessage
{
	CandyAmountMessage(const RecieverTypes aType, const unsigned short aCandyAmount) : BaseMessage(aType), myCandyAmount(aCandyAmount)
	{}

	const unsigned short myCandyAmount;
};

#pragma warning (pop)