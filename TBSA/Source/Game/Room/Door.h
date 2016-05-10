// Author:   Hampus Huledal
// CreationDate: 09/05/2016
#pragma once
#include <CU/Vectors/vector2.h>

class Door
{
public:
	Door();
	Door(unsigned int anId);
	~Door();

	void SetSecondId(unsigned int anId);

	Door& operator=(const Door& aDoor);

private:
	CommonUtilities::Vector2f myPosition;

	unsigned int myFirstId;
	unsigned int mySecondId;
	bool myCompleted;
	bool myIsSet;
};
