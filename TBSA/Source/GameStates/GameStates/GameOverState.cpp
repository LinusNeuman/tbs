#include "stdafx.h"
#include "GameOverState.h"
#include <string>

GameOverState::GameOverState(float aPoints, float aTurns, float aEnemies) :
myStatsBox({ 0.f, 0.f }, { 1000.f, 500.f }, "Text/calibril.ttf_sdf", eLinewrappingMode::Char)
{
	myLetThroughRender = true;
	myShouldExit = false;
	myShouldDisplayStats = false;

	myStatsBox.SetSize({ 1000.f, 500.f });
	myStatsBox.SetPosition({ 1920.f / 2.f - 80, 1080.f / 2.f - 340});
	myStatsBox.SetLines(9);

	std::string str = std::to_string(static_cast<int>(aPoints)) + " X CANDYBAG";
	if (aPoints > 1)
	{
		str.append("S");
	}
	myStatsBox.AddText(str);
	myStatsBox.AddText("");
	myStatsBox.AddText("");

	str = std::to_string(static_cast<int>(aEnemies)) + " X ENEMIES";
	myStatsBox.AddText(str);
	myStatsBox.AddText("");
	myStatsBox.AddText("");

	str = std::to_string(static_cast<int>(aTurns)) + " X TURNS";
	myStatsBox.AddText(str);
	myStatsBox.AddText("");
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

	myGameOverSprite = new StaticSprite();
	myGameOverSprite->Init("Sprites/GUI/EndScreens/gameOver.dds", false, CU::Vector4f::Zero, { 0.f, 0.f });
	myGameOverSprite->SetLayer(enumRenderLayer::eGUI);
	myGameOverSprite->SetRenderPriority(6000.f);

	LoadGUI("GameOver");

	myMouseController.Init();
	myTimer = 0;
}

eStackReturnValue GameOverState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	if (myShouldDisplayStats == true && myTimer > 200.f)
	{
		myGUIManager.StartRecieving();
	}
	else
	{
		myGUIManager.StopRecieving();
	}

	myGUIManager.Update(aDeltaTime);

	if (IsometricInput::GetAnyKeyPressed() == true || IsometricInput::GetAnyMouseButtonPressed() == true)
	{
		myShouldDisplayStats = true;
	}
	
	if (myShouldDisplayStats == true)
	{
		myTimer += aDeltaTime.GetMilliSeconds();
	}

	myMouseController.SetMouseState(enumMouseState::eClickedOnEmptyTile);

	myStatsBox.Update();
	
	if (myShouldExit == true)
	{
		myShouldExit = false;
		myTimer = 0.f;
		return eStackReturnValue::eDeleteSubstate;
	}
	return eStackReturnValue::eStay;
}

void GameOverState::Draw() const
{
	myMouseController.Draw(IsometricInput::GetMouseWindowPositionNormalizedSpace());
	if (myShouldDisplayStats == true)
	{
		myGUIManager.Render();
		myBackgroundSprite->DrawWithNormalized(CU::Vector2f(0.5f, 0.5f));
		myIcons->DrawWithNormalized(CU::Vector2f(0.48f, 0.54f));
		myStatsBox.Render();
	}
	if (myShouldDisplayStats == false)
	{
		myGameOverSprite->DrawWithNormalized(CU::Vector2f(0.f, 0.f));
	}
}

bool GameOverState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eGameOverReset)
	{
		myShouldExit = true;
	}
	return false;
}
