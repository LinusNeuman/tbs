#pragma once
#include <Rend/StaticSprite.h>
#include <CU/Timer/Time.h>
#include <StateStack/GameState.h>

class StaticSprite;
class RenderConverter;

enum class eSplashFadeState
{
	eFadingUp,
	eFadingDown
};

class Splash
{
public:
	Splash();
	Splash(const char* aPath);
	~Splash();

	bool Update(const CU::Time &aDeltaTime);
	void Render();
private:
	StaticSprite* mySprite;

	bool Fade(const CU::Time &aDelta);
	void FadeUp(const CU::Time &aDelta);
	void FadeDown(const CU::Time &aDelta);

	eSplashFadeState myFadeState;

	bool myIsDone;

	float myStayTimer;
};



class SplashState : public GameState
{
public:
	SplashState();
	~SplashState();
	void Init();
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;
private:
	StaticSprite * myBackgroundSprite;
	bool myShouldAdd;

	CU::StaticArray<Splash*, 2> mySplashes;
	uchar myCurrentSplash;

	float myWaitTimer;
};

