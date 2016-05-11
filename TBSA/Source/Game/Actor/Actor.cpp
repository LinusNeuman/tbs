#include "stdafx.h"
#include "Actor.h"
#include <Rend/WrappedSprite.h>


Actor::Actor(const CU::Vector2f &aStartPosition, const eActorType &aActorType)
{
	mySprite = new WrappedSprite();
	myPosition = aStartPosition;
	myVelocity = CU::Vector2f::Zero;
	myTargetPosition = myPosition;
	switch (aActorType)
	{
	case eActorType::ePlayerOne: 
		mySprite->Init("Sprites/camera3.png");
		mySprite->myLayer = 1;
		break;
	case eActorType::ePlayerTwo: 
		mySprite->Init("Sprites/camera7.png");
		mySprite->myLayer = 1;
		break;
	case eActorType::eEnemyOne: 
		mySprite->Init("Sprites/camera4.png");
		mySprite->myLayer = 1;
		break;
	case eActorType::eEnemyTwo: 
		mySprite->Init("Sprites/camera4.png");
		mySprite->myLayer = 1;
		break;
	default:
		break;
	}
}

Actor::~Actor()
{
}

void Actor::SetSelected(const bool aValue)
{
}

void Actor::Update(const CU::Time& aDeltaTime)
{
	myVelocity = (myTargetPosition - myPosition).GetNormalized() * 3.f;
	myPosition += myVelocity * aDeltaTime.GetSeconds();
}

void Actor::Draw() const
{
	mySprite->Draw(myPosition);
}

void Actor::Move(CU::Vector2f aTargetPosition)
{
	myTargetPosition = aTargetPosition;
}
