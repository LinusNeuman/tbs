#pragma once
#include <StateStack/GameState.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/StaticArray/StaticArray.h>
#include <unordered_map>
#include "../TextBox/TextBox.h"

class LevelFactory;
class GameLevel;

class PlayState : public GameState, public MessageReciever
{
public:
	PlayState();
	~PlayState();
	void Init(const std::string& aLevelPath = "");
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;
	

	void ChangeLevel(const std::string& aFilePath);

	virtual bool RecieveMessage(const GoalReachedMessage& aMessage) override;
	virtual bool RecieveMessage(const PlayerDiedMessage & aMessage) override;
	virtual bool RecieveMessage(const StartUpLevelMessage & aMessage) override;
	virtual bool RecieveMessage(const GUIMessage & aMessage) override;


private:
	GameLevel * myLevel;
	std::string myStartPath;
	std::string myLevelKey;
	std::string myCurrentLevelpath;
	LevelFactory* myLevelFactory;
	bool myShouldExit;
	bool myShouldPause;
};
