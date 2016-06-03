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
	void Init() override;
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;
	virtual void RecieveMessage(const StartUpLevelMessage & aMessage) override;
	void RecieveMessage(const PlayerDiedMessage & aMessage) override;

	void ChangeLevel(const std::string& aFilePath);
private:
	GameLevel * myLevel;
	std::string myStartPath;
	std::string myLevelKey;
	std::string myCurrentLevelpath;
	std::unordered_map<std::string, GameLevel*> myLevels;
	LevelFactory* myLevelFactory;
	bool myShouldExit;
};
