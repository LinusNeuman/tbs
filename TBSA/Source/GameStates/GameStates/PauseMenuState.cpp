#include "stdafx.h"
#include "PauseMenuState.h"


PauseMenuState::PauseMenuState()
{
	
}


PauseMenuState::~PauseMenuState()
{
	
}

void PauseMenuState::Init()
{
	myBackgroundSprite = new StaticSprite();
	myBackgroundSprite->Init("Sprites/GUI/PauseMenu/Background.dds", false);
	myBackgroundSprite->SetLayer(enumRenderLayer::eGUI);

	LoadGUI("PauseMenu");
}
