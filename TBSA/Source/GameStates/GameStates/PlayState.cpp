#include "stdafx.h"
#include "PlayState.h"

#include <Level/GameLevel.h>
#include <Message/StartUpLevelMessage.h>

PlayState::PlayState()
{
	myLevel = new GameLevel();
	myStartPath = "Data/Tiled/";;
}


PlayState::~PlayState()
{
	SAFE_DELETE(myLevel);
}

void PlayState::Init()
{
	//myLevel->Init();
	SingletonPostMaster::AddReciever(RecieverTypes::eStartUpLevel, *this);
	myLevels[myLevelKey] = new GameLevel();
	myLevels[myLevelKey]->Init(myStartPath + myLevelKey);
}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & /*aStateStack*/)
{
	//(aStateStack);
	static int index = 0;
	
	myLevels[myLevelKey]->Update(aTimeDelta);

	if (IsometricInput::GetKeyPressed(DIK_ESCAPE) == true)
	{
		return eStackReturnValue::ePopMain;
	}

	return eStackReturnValue::eStay;
}

void PlayState::Draw() const
{
	myLevels.at(myLevelKey)->Draw();
}

void PlayState::RecieveMessage(const StartUpLevelMessage& aMessage)
{
	myLevelKey = aMessage.myPath;
}
