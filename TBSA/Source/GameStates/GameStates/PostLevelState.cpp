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
	myText.SetPosition({ 1920.f / 2.f - 679.f / 2.f, 0.f });
	myText.SetLines(5);

	std::string str = "Candy collected: ";
	str.append(std::to_string(aPoints));
	myText.AddText(str);
	myText.AddText("");

	str = "Enemies disabled: ";
	str.append(std::to_string(aEnemies));
	myText.AddText(str);
	myText.AddText("");

	str = "Turned used: ";
	str.append(std::to_string(aTurns));
	myText.AddText(str);

	myLetThroughRender = true;
}

PostLevelState::~PostLevelState()
{
}

eStackReturnValue
PostLevelState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	myText.Update();

	if (IsometricInput::GetAnyMouseButtonPressed() == true || IsometricInput::GetAnyKeyPressed() == true)
	{
		return eStackReturnValue::eDeleteSubstate;
	}

	return eStackReturnValue::eStay;
}

void
PostLevelState::Draw() const
{
	myBg->Draw({ 1920.f / 2.f - 679.f / 2.f, 0 });
	myText.Render();
}