#include "stdafx.h"
#include "Actor.h"
#include <Rend/WrappedSprite.h>
#include "../Animation/Animation.h"


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
	CU::Vector2f distance = myVelocity * aDeltaTime.GetSeconds();
	if (myActiveAnimation != "")
	{
		myAnimations[myActiveAnimation]->UpdateAnimation();
		mySprite = myAnimations[myActiveAnimation]->GetSprite();
	}
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

void Actor::AddAnimation(Animation* anAnimation)
{
	myAnimations[anAnimation->GetName()] = anAnimation;
}

void Actor::ChangeAnimation(const std::string& anAnimation)
{
	if (myActiveAnimation != anAnimation)
	{
		if (myActiveAnimation != "")
		{
			if (myAnimations[myActiveAnimation]->GetIsRunning() == false || myAnimations[myActiveAnimation]->GetIsInteruptable() == true)
			{
				myAnimations[myActiveAnimation]->StopAnimation();
				if (myAnimations[myActiveAnimation]->GetInTransition() != "")
				{
					myAnimations[myAnimations[myActiveAnimation]->GetInTransition()]->SetHasPlayed(false);
				}
				if (myAnimations[myActiveAnimation]->GetOutTransition() != "")
				{
					myAnimations[myAnimations[myActiveAnimation]->GetOutTransition()]->SetHasPlayed(false);
				}

				if (myAnimations[myActiveAnimation]->GetOutTransition() == "" ||
					myAnimations[myAnimations[myActiveAnimation]->GetOutTransition()]->GetHasPlayed() == true)
				{
					if (myAnimations[anAnimation]->GetInTransition() == "" ||
						myAnimations[myAnimations[anAnimation]->GetInTransition()]->GetHasPlayed() == true)
					{
						myActiveAnimation = anAnimation;
					}
					else if (myActiveAnimation != myAnimations[anAnimation]->GetInTransition())
					{
						myActiveAnimation = myAnimations[anAnimation]->GetInTransition();
						myAnimations[myActiveAnimation]->StopAnimationAtEnd();
					}
				}
				else if (myActiveAnimation != myAnimations[anAnimation]->GetOutTransition())
				{
					myActiveAnimation = myAnimations[myActiveAnimation]->GetOutTransition();
					myAnimations[myActiveAnimation]->StopAnimationAtEnd();
				}
				myAnimations[myActiveAnimation]->StartAnimation();
			}
			else
			{
				myAnimations[myActiveAnimation]->StopAnimationAtEnd();
			}
		}
		else
		{
			myActiveAnimation = anAnimation;
			myAnimations[myActiveAnimation]->StartAnimation();
		}
	}
}