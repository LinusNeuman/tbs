#pragma once
#include <tga2d/Engine.h>
#include <StateStack/StateStack.h>

#include <CU/Thread/ThreadSynchronizer.h>
#include <GameStates/MenuState.h>
#include <GameStates/SplashState.h>
#include <ThreadPool/ThreadPool.h>


struct StartupData;

#pragma warning  (push)
#pragma warning(disable : 4512)

class CGame : public MessageReciever
{
public:
	CGame();
	~CGame();
	void Init(const std::wstring& aVersion = L"", HWND aHandle = nullptr);

	virtual bool RecieveMessage(const GUIMessage & aMessage) override;
	virtual bool RecieveMessage(const GetStartLevelMessage& aMessage) override;
	virtual bool RecieveMessage(const SetHWNDMessage & aMessage) override;
	

private:
	void InitCallBack();
	void UpdateCallBack();
	void UpdateWork();

	void RenderWork();
	void LogCallback(std::string aText);

	HWND myWindowHandle;

	StartupData * myStartupData;
	GameState * myMenuState;
	GameState * mySplashState;

	StateStack myGameStateStack;
	bool myImRunning;

	ThreadPool myThreadPool;
};
#pragma warning (pop)
