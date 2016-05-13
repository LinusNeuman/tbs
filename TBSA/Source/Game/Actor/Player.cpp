#include "stdafx.h"
#include "Player.h"
#include "Rend/Renderer.h"
#include <Rend/StaticSprite.h>


Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const CU::Vector2f& aStartPosition, const eActorType& aActorType)
{
	Actor::Init(aStartPosition, aActorType);
}
