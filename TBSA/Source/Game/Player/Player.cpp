#include "stdafx.h"
#include "Player.h"
#include "Rend/Renderer.h"
#include <Rend/WrappedSprite.h>


Player::Player()
{
	mySprite = new WrappedSprite();
	mySprite->Init("Sprites/camera3.png");
	mySprite->myLayer = 1;
	myPosition = CU::Vector2f(2, 2);
	myVelocity = CU::Vector2f::Zero;
	myTargetPosition = myPosition;
}

Player::~Player()
{
	delete mySprite;
}

void Player::Update(const CU::Time  aDeltaTime)
{
	myVelocity = (myTargetPosition - myPosition).GetNormalized() * 1.f;
	mySprite->SetPosition(myPosition);
	myPosition = myPosition + myVelocity * aDeltaTime.GetSeconds();
}

void Player::Draw() const
{
	mySprite->Draw();
}

void Player::Move(CU::Vector2f aTargetPosition, const CU::Time  aDeltaTime)
{
	myTargetPosition = aTargetPosition;
}

unsigned Player::GetSizeX() const
{
	return mySprite->GetSprite()->GetImageSize().x;
}

unsigned Player::GetSizeY() const
{
	return mySprite->GetSprite()->GetImageSize().y;
}
