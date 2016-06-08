// Author:   Hampus Huledal
// CreationDate: 07/06/2016
#pragma once
#include <StateStack/GameState.h>

struct TiledData;

class LoadState:public GameState
{
public:
	LoadState(TiledData* someData);
	~LoadState();

	eStackReturnValue Update(const CU::Time & aDeltaTime, ProxyStateStack & aStateStack) override;
	void Draw()const override;

private:
	TiledData* myDataptr;
	StaticSprite mySprite;
	CommonUtilities::Vector2f myPosition;
};
