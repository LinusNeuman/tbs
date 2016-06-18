#pragma once

#include "CU/NameSpaceAliases.h"

#include <CU/Timer/Time.h>

#include <string>
#include <CU/GrowingArray/GrowingArray.h>

#include <CU/Vectors/Vector.h>

#include <Rend/StaticSprite.h>
#include <Input/SingletoIsometricInputWrapper/SingletonIsometricInputWrapper.h>


#include <tga2d/text/text.h>

class Tooltip
{
public:
	Tooltip();
	virtual ~Tooltip();

	void Init(const char* aText, CU::Vector2i aSizeInPixels, float aShowDelay);

	void Show();
	void Close();
	
	void Update(const CU::Time &aDelta);

	void Render();
protected:
	void Reset();

	StaticSprite* myBackground;

	DX2D::CText* myText;
	CU::Vector4f myTextColor;

	

	CU::Vector2i mySizeInPixels;

	float myTimeUntilShow;
	float myCurrentTimeDelayed;

	bool myIsTriggered;
	bool myShouldShow;
};