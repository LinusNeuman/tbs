#include "stdafx.h"
#include "GameState.h"

#include <GUI/Managing/GUIFactory.h>


GameState::GameState(const char* aName)
{
	myLetThroughRender = false;
	myName = aName;
}


GameState::~GameState()
{
}

void GameState::Init()
{
	myGUIElements = GUIFactory::GetInstance()->GetLoadedGUI(myName);
}

bool GameState::GetShouldLetThroughRendering()
{
	return myLetThroughRender;
}

