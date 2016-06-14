#include "stdafx.h"
#include "LoadState.h"
#include <TiledData/TiledData.h>

LoadState::LoadState(TiledData* someData)
{
	myDataptr = someData;
	mySpriteLoading.Init("Sprites/LoadingScreen/loading.dds", false, CU::Vector4f::Zero, {0.5f, 0.5f});
	myDoneSprite.Init("Sprites/LoadingScreen/pressAnyKey.dds", false, CU::Vector4f::Zero, { 0.5f, 0.5f });
	myDotSprite.Init("Sprites/LoadingScreen/dot1.dds", false);
	myBackGround.Init("Sprites/mainmenu.dds", false, { 0.f, 0.f, 1920.f, 1080 }, { 0.5f, 0.5f });

	myTimer.SetAlarmTimeLength(0.5f);
	myDotCounter = 0;
}

LoadState::~LoadState()
{
}

eStackReturnValue LoadState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	if (myDataptr->myIsLoaded == true)
	{
		if (IsometricInput::GetAnyKeyPressed() == true || IsometricInput::GetAnyMouseButtonPressed() == true)
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
				myDotCounter = 0;
			}
		}
	}

	
	return  eStackReturnValue::eStay;
}

void LoadState::Draw() const 
{
	myBackGround.DrawWithNormalized({ 0.5f, 0.5f });

	if (myDataptr->myIsLoaded == true)
	{
		myDoneSprite.DrawWithNormalized({ 0.5f, 0.5f });
	}
	else
	{
		mySpriteLoading.DrawWithNormalized({ 0.5f, 0.5f });

		for (unsigned short iDot = 0; iDot < myDotCounter; ++iDot)
		{
			myDotSprite.DrawWithNormalized({ 0.4f + (0.05f * FLOATCAST(iDot)), 0.6f });
		}
	}
}
