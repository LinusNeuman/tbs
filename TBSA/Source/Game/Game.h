#pragma once
#include <tga2d/Engine.h>
#include "GameWorld.h"
#include <StateStack.h>


class CGame
{
public:
	CGame();
	~CGame();
	void Init(const std::wstring& aVersion = L"");
private:
	void InitCallBack();
	void UpdateCallBack();
	void LogCallback(std::string aText);

	GameState * myGameWorld;
	GameState * myTextState;
	GameState * myKakaState;
	GameState * mySubStateGameWorld;
	GameState * mySubStateTextState;
	GameState * mySubStateKakaState;

	StateStack myGameStateStack;
	bool myImRunning;
};
