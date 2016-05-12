#include "stdafx.h"
#include "Actor.h"
#include <Rend/WrappedSprite.h>
#include <tga2d/math/vector2.h>


Actor::Actor()
{
	mySprite = new WrappedSprite();
	myVelocity = CU::Vector2f::Zero;
}

Actor::~Actor()
{
}

void Actor::Init(const CU::Vector2f& aStartPosition, const eActorType& aActorType)
{
	myPosition = aStartPosition;
	myTargetPosition = myPosition;
	switch (aActorType)
	{
	case eActorType::ePlayerOne:
		mySprite->Init("Sprites/camera3.png");
		mySprite->SetLayer(enumRenderLayer::eGameObjects);
		break;
	case eActorType::ePlayerTwo:
		mySprite->Init("Sprites/camera7.png");
		mySprite->SetLayer(enumRenderLayer::eGameObjects);
		break;
	case eActorType::eEnemyOne:
		mySprite->Init("Sprites/camera4.png");
		mySprite->SetLayer(enumRenderLayer::eGameObjects);
		break;
	case eActorType::eEnemyTwo:
		mySprite->Init("Sprites/camera4.png");
		mySprite->SetLayer(enumRenderLayer::eGameObjects);
		break;
	default:
		break;
	}
}

void Actor::SetSelected(const bool aValue)
{
}

void Actor::Update(const CU::Time& aDeltaTime)
{
	myVelocity = (myTargetPosition - myPosition).GetNormalized() * 3.f;
	myPosition += myVelocity * aDeltaTime.GetSeconds();
	CU::Vector2f distance = myVelocity * aDeltaTime.GetSeconds();
	if ((myTargetPosition - myPosition).Length() <= distance.Length())
	{
		myTargetPosition = myPosition;
	}
}

void Actor::Draw() const
{
	mySprite->Draw(myPosition);
}

void Actor::Move(CU::Vector2f aTargetPosition)
{
	myTargetPosition = aTargetPosition;
}
