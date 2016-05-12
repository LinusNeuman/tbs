#pragma once
#include <tga2d/Engine.h>
#include "GameWorld.h"
#include <StateStack.h>

#include "../ThreadPool/Source/ThreadPool.h"
#include <CU/Thread/ThreadSynchronizer.h>
#pragma warning  (push)
#pragma warning(disable : 4512)
class CGame
{
public:
	CGame();
	~CGame();
	void Init(const std::wstring& aVersion = L"");
private:
	void InitCallBack();
	void UpdateCallBack();
	void UpdateWork();

	void RenderWork();
	void LogCallback(std::string aText);

	GameState * myGameWorld;

	StateStack myGameStateStack;
	bool myImRunning;

	ThreadPool myThreadPool;
};
#pragma warning (pop)
