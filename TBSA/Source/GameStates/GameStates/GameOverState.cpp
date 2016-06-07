#include "stdafx.h"
#include "GameOverState.h"


GameOverState::GameOverState()
{
	myLetThroughRender = true;
}


GameOverState::~GameOverState()
{
}

void GameOverState::Init()
{
	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/GUI/InGame/GameOver/Background.dds", false);
	myBackgroundSprite->SetLayer(enumRenderLayer::eGUI);
	LoadGUI("GameOver");
}

eStackReturnValue GameOverState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	return eStackReturnValue::eStay;
}

void GameOverState::Draw() const
{
	myBackgroundSprite->Draw(CU::Vector2f(0, 0.f));
}

