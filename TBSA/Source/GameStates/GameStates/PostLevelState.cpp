#include "stdafx.h"
#include "PostLevelState.h"
#include <Rend\RenderConverter.h>

PostLevelState::PostLevelState(unsigned int aPoints, unsigned int aTurns, unsigned int aEnemies):
	myText({ 0.f, 0.f }, {1000.f, 500.f}, "Text/calibril.ttf_sdf", eLinewrappingMode::Char)
{
	myText.SetSize({ 1000.f, 500.f });
	myText.SetPosition({0.f, 0.f});
	myText.SetLines(5);

	std::string str = (std::to_string(aPoints));
	myText.AddText(str);

	str = (std::to_string(aEnemies));
	myText.AddText(str);

	str = (std::to_string(aTurns));
	myText.AddText(str);

	myText.AddText("");
	myText.AddText("Click to continue!");

	myLetThroughRender = false;
	myRender = true;
}

PostLevelState::~PostLevelState()
{
}

eStackReturnValue
PostLevelState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	myText.Update();

	if (IsometricInput::GetAnyMouseButtonPressed() == true)
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
		myText.Render();
	}
}