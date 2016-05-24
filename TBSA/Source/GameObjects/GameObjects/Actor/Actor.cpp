#include "stdafx.h"
#include "Actor.h"
#include <Rend/StaticSprite.h>
//#include <tga2d/math/vector2.h>
#include <Animation/Animation.h>
//#include "../JsonDataStructs.h"
#include "GameObjects/JsonDataStructs.h"
#include <CU\DLDebug\DL_Debug.h>


Actor::Actor()
{
	mySprite = new StaticSprite();
	myVelocity = CU::Vector2f::Zero;
	myAP = 5;
}

Actor::~Actor()
{
}

void Actor::Init(const ActorData &aActorData)
{
	myPosition = aActorData.myPosition;
	myTargetPosition = myPosition;
	mySprite->Init();
	mySprite->SetLayer(enumRenderLayer::eGameObjects);
	mySprite->SetPivotWithPixels(CU::Vector2f(64.f, 32.f));
	myAnimations = aActorData.myAnimations;
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
		mySprite->SetLayer(enumRenderLayer::eGameObjects);
		mySprite->SetPivotWithPixels(CU::Vector2f(64.f, 32.f));
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

int Actor::GetMyAP()
{
	return myAP;
}

void Actor::ChangeAnimation(const std::string& anAnimation)
{
	DL_ASSERT(myAnimations.find(anAnimation) != myAnimations.end(), "Animation does not exist");
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
