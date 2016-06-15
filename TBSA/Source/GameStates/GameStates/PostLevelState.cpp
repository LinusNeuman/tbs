#include "stdafx.h"
#include "PostLevelState.h"
#include <Rend\RenderConverter.h>

PostLevelState::PostLevelState(unsigned int aPoints, unsigned int aTurns, unsigned int aEnemies):
	myText({ 0.f, 0.f }, {1000.f, 500.f}, "Text/calibril.ttf_sdf", eLinewrappingMode::Char)
{
	myBg = new StaticSprite();
	myBg->Init("Sprites/GUI/PostLevel/bg.dds", false, { 0, 0, 679, 564 }, { 0, 0 });
	myBg->SetLayer(enumRenderLayer::eGUI);

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

	myLetThroughRender = true;
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
		return eStackReturnValue::eDeleteSubstate;
	}

	return eStackReturnValue::eStay;
}

void
PostLevelState::Draw() const
{
	myBg->Draw({0, 0});
	myText.Render();
}