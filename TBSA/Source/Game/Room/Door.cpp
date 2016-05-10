#include "stdafx.h"
#include "Door.h"

Door::Door()
{
}

Door::Door(unsigned anId)
{
	myFirstId = anId;
	myCompleted = false;
}

Door::~Door()
{
}

void Door::SetSecondId(unsigned anId)
{
	mySecondId = anId;
	myCompleted = true;
}
