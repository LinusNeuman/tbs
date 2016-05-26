#include "stdafx.h"
#include "GameState.h"
#include "../../GUI/GUI/Managing/GUIFactory.h"


GameState::GameState()
{
	myLetThroughRender = false;
}


GameState::~GameState()
{
	if (myGUIElements != nullptr)
	{
		myGUIElements->RemoveAll();
		delete myGUIElements;
	}
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

