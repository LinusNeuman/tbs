#pragma once
#include "RecieverTypes.h"

class MessageEvent;

struct Message
{

	Message(const RecieverTypes aRecieverType, const MessageEvent & aEventPointer) :
		myEventPointer(aEventPointer),
		myMessageType(aRecieverType)
	{}

	const MessageEvent & myEventPointer;
	RecieverTypes myMessageType;
};