#pragma once
#include <StateStack/GameState.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/StaticArray/StaticArray.h>
#include <unordered_map>


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

private:
	GameLevel * myLevel;
	std::string myStartPath;
	std::string myLevelKey;
	std::unordered_map<std::string, GameLevel*> myLevels;
};
