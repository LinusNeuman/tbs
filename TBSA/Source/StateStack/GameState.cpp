#include "stdafx.h"
#include "GameState.h"



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

bool GameState::GetShouldLetThroughRendering()
{
	return myLetThroughRender;
}

