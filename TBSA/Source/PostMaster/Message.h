#pragma once
#include "RecieverTypes.h"

class Event;

struct Message
{

	Message(const RecieverTypes aRecieverType, const Event & aEventPointer) :
		myEventPointer(aEventPointer),
		myMessageType(aRecieverType)
	{}

	const Event & myEventPointer;
	RecieverTypes myMessageType;
};