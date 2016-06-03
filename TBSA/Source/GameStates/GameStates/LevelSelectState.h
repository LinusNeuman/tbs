#pragma once
#include <StateStack/GameState.h>

class StaticSprite;
class RenderConverter;

class LevelSelectState : public GameState, public MessageReciever
{
public:
	LevelSelectState();
	~LevelSelectState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

	bool RecieveMessage(const GUIMessage & aMessage) override;
private:
	StaticSprite * myBackgroundSprite;
	std::string mySelectedLevel;
};

