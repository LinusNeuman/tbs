#include "stdafx.h"
#include "MenuState.h"
#include <CU/Vectors/Vector2.h>
#include <Rend/StaticSprite.h>
#include <StateStack/ProxyStateStack.h>
#include "PlayState.h"

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

void MenuState::Init()
{
	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/mainMenu.dds", false);
	myBackgroundSprite->SetLayer(enumRenderLayer::eGameObjects);

	LoadGUI("MainMenu");
}

eStackReturnValue MenuState::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{
	(aTimeDelta);
	if (IsometricInput::GetKeyPressed(DIK_RETURN) == true || IsometricInput::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eRight) == true)
	{
		PlayState *newState = new PlayState();
		newState->Init();
		aStateStack.AddMainState(newState);
	}
	return eStackReturnValue::eStay;
}

void MenuState::Draw() const
{
	myBackgroundSprite->Draw(CU::Vector2f(0, 0));
}
