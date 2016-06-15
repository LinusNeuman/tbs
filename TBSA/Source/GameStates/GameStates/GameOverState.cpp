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
	myBackgroundSprite->Init("Sprites/GUI/EndScreens/EndFail_Background.dds", false, CU::Vector4f(0.f,0.f,680.f,563.f), { 0.5f, 0.5f });
	myBackgroundSprite->SetLayer(enumRenderLayer::eGUI);
	myBackgroundSprite->SetRenderPriority(600.f);

	LoadGUI("GameOver");
}

eStackReturnValue GameOverState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	myGUIManager.Update(aDeltaTime);
	if (myShouldExit == true)
	{
		myShouldExit = false;
		//return eStackReturnValue::ePopSubState;
		return eStackReturnValue::eDeleteSubstate;
	}
	return eStackReturnValue::eStay;
}

void GameOverState::Draw() const
{
	myGUIManager.Render();
	myBackgroundSprite->DrawWithNormalized(CU::Vector2f(0.5f, 0.5f));
}

bool GameOverState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eGameOverReset)
	{
		myShouldExit = true;
	}
	return false;
}
