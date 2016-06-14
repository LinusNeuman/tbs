#include "stdafx.h"
#include "LoadState.h"
#include <TiledData/TiledData.h>

LoadState::LoadState(TiledData* someData)
{
	myDataptr = someData;
	myPosition = CommonUtilities::Vector2f::Zero;
	mySprite.Init("Sprites/Splash/Group.dds", false);
}

LoadState::~LoadState()
{
}

eStackReturnValue LoadState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	if (myDataptr->myIsLoaded == true)
	{
		if (IsometricInput::GetAnyKeyReleased() == true || IsometricInput::GetAnyMouseButtonReleased() == true)
		{
			return eStackReturnValue::eDeleteMainState;
		}
	}
	else
	{
		myPosition += CommonUtilities::Vector2f(100, 100) * aDeltaTime.GetSeconds();
	}

	
	return  eStackReturnValue::eStay;
}

void LoadState::Draw() const 
{
	mySprite.Draw(myPosition);
}
