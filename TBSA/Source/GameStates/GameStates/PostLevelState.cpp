#include "stdafx.h"
#include "PostLevelState.h"
#include <Rend\RenderConverter.h>

PostLevelState::PostLevelState(unsigned int aPoints, unsigned int aTurns, unsigned int aEnemies):
	myEnemiesText({ 0.f, 0.f }, {500.f, 100.f}, "Text/calibril.ttf_sdf"),
	myPointsText({ 0.f, 100.f }, { 500.f, 100.f }, "Text/calibril.ttf_sdf"),
	myTurnsText({ 0.f, 200.f }, { 500.f, 100.f }, "Text/calibril.ttf_sdf"),
	myInfoText({ 0.f, 300.f }, { 500.f, 100.f }, "Text/calibril.ttf_sdf")
{
	std::string str("Points: ");
	str.append(std::to_string(aPoints));
	myPointsText.AddText(str);

	str = "Enemies: ";
	str.append(std::to_string(aEnemies));
	myEnemiesText.AddText(str);

	str = "Turns: ";
	str.append(std::to_string(aTurns));
	myTurnsText.AddText(str);

	myInfoText.AddText("Press 'Enter' to continue!");

	myLetThroughRender = false;
	myRender = true;
}

PostLevelState::~PostLevelState()
{
}

eStackReturnValue
PostLevelState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	myEnemiesText.Update();
	myPointsText.Update();
	myTurnsText.Update();
	myInfoText.Update();

	if (IsometricInput::GetKeyDown(DIK_RETURN) == true)
	{
		myRender = false;
		RenderConverter::ClearCommands();
		return eStackReturnValue::eDeleteSubstate;
	}

	return eStackReturnValue::eStay;
}

void
PostLevelState::Draw() const
{
	if (myRender == true)
	{
		myEnemiesText.Render();
		myTurnsText.Render();
		myPointsText.Render();
		myInfoText.Render();
	}
}