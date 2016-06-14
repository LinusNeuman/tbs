// Author:   Hampus Huledal
// CreationDate: 07/06/2016
#pragma once
#include <StateStack/GameState.h>
#include <CU/Timer/Alarm.h>

struct TiledData;

class LoadState:public GameState
{
public:
	LoadState(TiledData* someData);
	~LoadState();

	eStackReturnValue Update(const CU::Time & aDeltaTime, ProxyStateStack & aStateStack) override;
	void Draw()const override;

private:
	CU::Alarm myTimer;
	unsigned short myDotCounter;

	TiledData* myDataptr;
	StaticSprite myBackGround;
	StaticSprite mySpriteLoading;
	StaticSprite myDoneSprite;
	StaticSprite myDotSprite;
};
