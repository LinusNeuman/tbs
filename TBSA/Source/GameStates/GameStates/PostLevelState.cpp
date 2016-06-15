#include "stdafx.h"
#include "PostLevelState.h"
#include <Rend\RenderConverter.h>

PostLevelState::PostLevelState(int aPoints, int aTurns, int aEnemies):
	myText({ 0.f, 0.f }, {1000.f, 500.f}, "Text/calibril.ttf_sdf", eLinewrappingMode::Char)
{
	myBg = new StaticSprite();
	myBg->Init("Sprites/GUI/PostLevel/bg.dds", false, CU::Vector4f(0.f, 0.f, 680.f, 563.f), { 0.5f, 0.5f });
	myBg->SetLayer(enumRenderLayer::eGUI);

	myText.SetSize({ 1000.f, 500.f });
	myText.SetPosition({ 1920.f / 2.f - 579.f / 2.f, 0.f });
	myText.SetLines(9);

	std::string str = std::to_string(aPoints) + " X CANDYBAG";
	if (aPoints > 1)
	{
		str.append("S");
	}
	myText.AddText(str);
	myText.AddText("");

	str = std::to_string(aEnemies) + " X ENEMIES";
	myText.AddText(str);
	myText.AddText("");

	str = std::to_string(aTurns) + " X TURNS";
	myText.AddText(str);
	myText.AddText("");

	str = "Press any key to continue.";
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