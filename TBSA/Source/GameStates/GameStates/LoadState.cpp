#include "stdafx.h"
#include "LoadState.h"
#include <TiledData/TiledData.h>

LoadState::LoadState(TiledData* someData)
{
	myDataptr = someData;
	mySprite.Init("Sprites/LoadingScreen/loading.dds", false, CU::Vector4f::Zero, {0.5f, 0.5f});
	myDoneSprite.Init("Sprites/LoadingScreen/pressAnyKey.dds", false, CU::Vector4f::Zero, { 0.5f, 0.5f });
	myDotSprite.Init("Sprites/LoadingScreen/dot1.dds", false);

	myTimer.SetAlarmTimeLength(0.5f);
	myDotCounter = 1;
}

LoadState::~LoadState()
{
}

eStackReturnValue LoadState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	if (myDataptr->myIsLoaded == false)
	{
		if (IsometricInput::GetAnyKeyReleased() == true || IsometricInput::GetAnyMouseButtonReleased() == true)
		{
			return eStackReturnValue::eDeleteMainState;
		}
	}
	else
	{
		if (myTimer.GetProgress() >= 1.f)
		{
			myTimer.Reset();
			++myDotCounter;

			if (myDotCounter > 3)
			{
				myDotCounter = 1;
			}
		}
	}

	
	return  eStackReturnValue::eStay;
}

void LoadState::Draw() const 
{
	if (myDataptr->myIsLoaded == false)
	{
		myDoneSprite.DrawWithNormalized({ 0.5f, 0.5f });
	}
	else
	{
		mySprite.DrawWithNormalized({ 0.5f, 0.5f });

		for (unsigned short iDot = 0; iDot < myDotCounter; ++iDot)
		{
			myDotSprite.DrawWithNormalized({ 0.4f + (0.05f * FLOATCAST(iDot)), 0.6f });
		}
	}
}
