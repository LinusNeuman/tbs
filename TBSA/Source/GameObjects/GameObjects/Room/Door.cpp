#include "stdafx.h"
#include "Door.h"

Door::Door()
{
	myCompleted = false;
	myIsSet = false;
}

Door::Door(unsigned anId)
{
	myFirstId = anId;
	myCompleted = false;
	myIsSet = true;
}

Door::~Door()
{
}

void Door::SetSecondId(unsigned anId)
{
	mySecondId = anId;
	myCompleted = true;
}

Door& Door::operator=(const Door& aDoor)
{
	if (aDoor.myCompleted == false || aDoor.myPosition != myPosition)
	{
		if (myIsSet == false)
		{
			myFirstId = aDoor.myFirstId;
			myIsSet = true;
		}
		else if (myCompleted == false)
		{
			mySecondId = aDoor.myFirstId;
			myCompleted = true;
		}
		else
		{
			DL_PRINT("WARNING: assigning an uncompleted door to a completed one");
			myFirstId = aDoor.myFirstId;
			mySecondId = aDoor.mySecondId;
			myPosition = aDoor.myPosition;
		}
	}
	else
	{
		myFirstId = aDoor.myFirstId;
		mySecondId = aDoor.mySecondId;
		myPosition = aDoor.myPosition;
		myCompleted = aDoor.myCompleted;
		myIsSet = aDoor.myIsSet;
	}

	return *this;
}
