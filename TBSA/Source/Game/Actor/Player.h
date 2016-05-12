#pragma once
#include "Actor.h"


class RenderConverter;
class WrappedSprite;

class Player : public Actor 
{
public:
	Player();
	~Player();
	void Init(const CU::Vector2f &aStartPosition, const eActorType &aActorType);
private:
};

