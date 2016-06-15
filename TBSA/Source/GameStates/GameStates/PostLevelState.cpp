#include "stdafx.h"
#include "PostLevelState.h"
#include <Rend\RenderConverter.h>

PostLevelState::PostLevelState(int aPoints, int aTurns, int aEnemies):
	myText({ 0.f, 0.f }, {1000.f, 500.f}, "Text/calibril.ttf_sdf", eLinewrappingMode::Char)
{
	myIsExit = false;

	myBg = new StaticSprite();
	myBg->Init("Sprites/GUI/PostLevel/bg.dds", false, CU::Vector4f(0.f, 0.f, 680.f, 563.f), { 0.5f, 0.5f });
	myBg->SetLayer(enumRenderLayer::eGUI);
	myBg->SetRenderPriority(600);

	myIcons = new StaticSprite();
	myIcons->Init("Sprites/GUI/EndScreens/Icons.dds", false, CU::Vector4f::Zero, { 0.5f, 0.5f });
	myIcons->SetLayer(enumRenderLayer::eGUI);
	myIcons->SetRenderPriority(700.f);

	myText.SetSize({ 1000.f, 500.f });
	myText.SetPosition({ 1920.f / 2.f - 80, 1080.f / 2.f - 340 });
	myText.SetLines(9);

	std::string str = std::to_string(static_cast<int>(aPoints)) + " X CANDYBAG";
	if (aPoints > 1)
	{
		str.append("S");
	}
	myText.AddText(str);
	myText.AddText("");
	myText.AddText("");

	str = std::to_string(static_cast<int>(aEnemies)) + " X ENEMIES";
	myText.AddText(str);
	myText.AddText("");
	myText.AddText("");

	str = std::to_string(static_cast<int>(aTurns)) + " X TURNS";
	myText.AddText(str);
	myText.AddText("");
	myText.AddText("");

	myLetThroughRender = true;

	SingletonPostMaster::AddReciever(RecieverTypes::eContinueEndScreen, *this);

	LoadGUI("PostGame");
}

PostLevelState::~PostLevelState()
{
	SingletonPostMaster::RemoveReciever(*this);
}

eStackReturnValue
PostLevelState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	myGUIManager.Update(aDeltaTime);
	myText.Update();

	if (myIsExit == true)
	{
		myIsExit = false;
		return eStackReturnValue::eDeleteSubstate;
	}

	return eStackReturnValue::eStay;
}

void
PostLevelState::Draw() const
{
	myGUIManager.Render();
	myBg->DrawWithNormalized(CU::Vector2f(0.5f, 0.5f));
	myIcons->DrawWithNormalized(CU::Vector2f(0.48f, 0.54f));
	myText.Render();
}

bool
PostLevelState::RecieveMessage(const GUIMessage &aMessage)
{
	if (aMessage.myType == RecieverTypes::eContinueEndScreen)
	{
		myIsExit = true;
	}
	return true;
}