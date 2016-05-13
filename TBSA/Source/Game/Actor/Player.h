#pragma once
#include "Actor.h"


struct ActorData;
class RenderConverter;
class WrappedSprite;

class Player : public Actor 
{
public:
	Player();
	~Player();
	void Init(ActorData aActorData);
private:
};

