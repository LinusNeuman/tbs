#pragma once
#include "Game.h"


class RenderConverter;
class WrappedSprite;

class Player
{
public:
	Player(RenderConverter* aRenderConverter);
	~Player();
	void Update(const CU::Time aDeltaTime);
	void Draw();
private:
	WrappedSprite *mySprite;
};

