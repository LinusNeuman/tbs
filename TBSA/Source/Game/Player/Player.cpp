#include "stdafx.h"
#include "Player.h"
#include "Rend/Renderer.h"
#include <Rend/WrappedSprite.h>


Player::Player(RenderConverter* aRenderConverter)
{
	mySprite = new WrappedSprite(*aRenderConverter);
}

Player::~Player()
{
}

void Player::Update(const CU::Time  aDeltaTime)
{

}

void Player::Draw()
{
	mySprite->Draw();
}
