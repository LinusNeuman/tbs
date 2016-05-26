#pragma once
#include <tga2d/Engine.h>
#include <StateStack/StateStack.h>

#include <CU/Thread/ThreadSynchronizer.h>
#include <GameStates/MenuState.h>
#include <ThreadPool/ThreadPool.h>
#pragma warning  (push)
#pragma warning(disable : 4512)

class CGame : public MessageReciever
{
public:
	CGame();
	~CGame();
	void Init(const std::wstring& aVersion = L"");

	void RecieveMessage(const GUIMessage & aMessage) override;
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
