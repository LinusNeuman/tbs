#include "stdafx.h"
#include "PlayState.h"

#include <Level/GameLevel.h>

PlayState::PlayState()
{
	myLevel = new GameLevel();
}


PlayState::~PlayState()
{
	SAFE_DELETE(myLevel);
}

void PlayState::Init()
{
	myLevel->Init();
}

eStackReturnValue PlayState::Update(const CU::Time & aTimeDelta, ProxyStateStack & /*aStateStack*/)
{
	//(aStateStack);
	static int index = 0;
	

	myLevel->Update(aTimeDelta);

	if (IsometricInput::GetKeyPressed(DIK_ESCAPE) == true)
	{
		return eStackReturnValue::ePopMain;
	}

	return eStackReturnValue::eStay;
}

void PlayState::Draw() const
{
	myLevel->Draw();
}

