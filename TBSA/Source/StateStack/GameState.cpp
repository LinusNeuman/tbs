#include "stdafx.h"
#include "GameState.h"

#include <GUI/Managing/GUIFactory.h>


GameState::GameState()
{
	myLetThroughRender = false;
}


GameState::~GameState()
{
}

void GameState::Init()
{
	
}

void GameState::LoadGUI(const char* aName)
{
	myGUIElements = GUIFactory::GetInstance()->GetLoadedGUI(aName);
}


bool GameState::GetShouldLetThroughRendering()
{
	return myLetThroughRender;
}

