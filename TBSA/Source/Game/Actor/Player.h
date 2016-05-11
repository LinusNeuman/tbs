#pragma once
#include "Actor.h"


class RenderConverter;
class WrappedSprite;

class Player : public Actor 
{
public:
	Player(const CU::Vector2f &aStartPosition, const eActorType &aActorType);
	~Player();
private:
};

