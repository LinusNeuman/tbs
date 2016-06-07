#include "stdafx.h"
#include "GameOverState.h"


GameOverState::GameOverState()
{
	myLetThroughRender = true;
	myShouldExit = false;
}


GameOverState::~GameOverState()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eGameOverReset, *this);
}

void GameOverState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eGameOverReset, *this);

	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/GUI/InGame/GameOver/Background.dds", false);
	myBackgroundSprite->SetLayer(enumRenderLayer::eGUI);
	LoadGUI("GameOver");
}

eStackReturnValue GameOverState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	myGUIManager.Update(aDeltaTime);
	if (myShouldExit == true)
	{
		myShouldExit = false;
		return eStackReturnValue::ePopSubState;
	}
	return eStackReturnValue::eStay;
}

void GameOverState::Draw() const
{
	myGUIManager.Render();
	myBackgroundSprite->Draw(CU::Vector2f(0, 0.f));
}

bool GameOverState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eGameOverReset)
	{
		myShouldExit = true;
	}
	return false;
}
