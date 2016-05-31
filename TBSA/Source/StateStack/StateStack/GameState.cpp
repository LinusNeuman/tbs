#include "stdafx.h"
#include "GameState.h"
#include "../../GUI/GUI/Managing/GUIFactory.h"


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
	myGUIManager.LoadActiveGUI(GUIFactory::GetInstance()->GetLoadedGUI(aName));
}

bool GameState::GetShouldLetThroughRendering()
{
	return myLetThroughRender;
}

