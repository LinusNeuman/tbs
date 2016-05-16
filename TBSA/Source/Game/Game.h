#pragma once
#include <tga2d/Engine.h>
#include <StateStack/StateStack.h>

#include <Source/ThreadPool.h>
#include <CU/Thread/ThreadSynchronizer.h>
#include <GameStates/MenuState.h>
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

	GameState * myMenuState;

	StateStack myGameStateStack;
	bool myImRunning;

	ThreadPool myThreadPool;
};
#pragma warning (pop)
