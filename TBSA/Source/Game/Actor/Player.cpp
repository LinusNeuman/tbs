#include "stdafx.h"
#include "Player.h"
#include "Rend/Renderer.h"
#include <Rend/WrappedSprite.h>


Player::Player(const CU::Vector2f &aStartPosition, const eActorType &aActorType) : Actor(aStartPosition, aActorType)
{
}

Player::~Player()
{
}

