#include "stdafx.h"
#include "GameOverState.h"
#include <string>

GameOverState::GameOverState(float aPoints, float aTurns, float aEnemies) :
myStatsBox({ 0.f, 0.f }, { 1000.f, 500.f }, "Text/calibril.ttf_sdf", eLinewrappingMode::Char)
{
	myLetThroughRender = true;
	myShouldExit = false;

	myStatsBox.SetSize({ 1000.f, 500.f });
	myStatsBox.SetPosition({ 1920.f / 2.f - 579.f / 2.f, 0.5f });
	myStatsBox.SetLines(9);

	std::string str = std::to_string(static_cast<int>(aPoints)) + " X CANDYBAG";
	if (aPoints > 1)
	{
		str.append("S");
	}
	myStatsBox.AddText(str);
	myStatsBox.AddText("");

	str = std::to_string(static_cast<int>(aEnemies)) + " X ENEMIES";
	myStatsBox.AddText(str);
	myStatsBox.AddText("");

	str = std::to_string(static_cast<int>(aTurns)) + " X TURNS";
	myStatsBox.AddText(str);
	myStatsBox.AddText("");

	myLetThroughRender = true;
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

	myIcons = new StaticSprite();
	myIcons->Init("Sprites/GUI/EndScreens/Icons.dds", false, CU::Vector4f::Zero, { 0.5f, 0.5f });
	myIcons->SetLayer(enumRenderLayer::eGUI);
	myIcons->SetRenderPriority(700.f);

	LoadGUI("GameOver");
}

eStackReturnValue GameOverState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	myGUIManager.Update(aDeltaTime);

	myStatsBox.Update();

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
	myIcons->DrawWithNormalized(CU::Vector2f(0.48f, 0.54f));
	myStatsBox.Render();
}

bool GameOverState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eGameOverReset)
	{
		myShouldExit = true;
	}
	return false;
}
