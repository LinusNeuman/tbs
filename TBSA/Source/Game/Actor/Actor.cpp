#include "stdafx.h"
#include "Actor.h"
#include <Rend/WrappedSprite.h>


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
		/*mySprite->GetSprite()->SetTextureRect(0.25f, 0.0, 0.5f, 0.5f);
		mySprite->GetSprite()->SetSize(DX2D::Vector2f(mySprite->GetSprite()->GetSize().x / 4, mySprite->GetSprite()->GetSize().y / 2));*/
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
}

void Actor::Draw() const
{
	mySprite->Draw(myPosition);
}

void Actor::Move(CU::Vector2f aTargetPosition)
{
	myTargetPosition = aTargetPosition;
}
