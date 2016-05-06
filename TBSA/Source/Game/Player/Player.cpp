#include "stdafx.h"
#include "Player.h"
#include "Rend/Renderer.h"
#include <Rend/WrappedSprite.h>


Player::Player(const CU::Vector2f &aStartPosition, const unsigned aId)
{
	mySprite = new WrappedSprite();
	mySprite->Init("Sprites/camera3.png");
	mySprite->myLayer = 1;
	myPosition = aStartPosition;
	myVelocity = CU::Vector2f::Zero;
	myTargetPosition = myPosition;
	myId = aId;
	if (myId == 1)
		myIsSelected = true;
	else
		myIsSelected = false;

}

Player::~Player()
{
	delete mySprite;
}

void Player::Update(const CU::Time  aDeltaTime)
{
	myVelocity = (myTargetPosition - myPosition).GetNormalized() * 3.f;
	myPosition += myVelocity * aDeltaTime.GetSeconds();
}

void Player::Draw() const
{
	mySprite->Draw(myPosition);
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

void Player::SetSelected(const bool aValue)
{
	myIsSelected = aValue;
}
