#include "stdafx.h"
#include "Actor.h"
#include <Rend/StaticSprite.h>
//#include <tga2d/math/vector2.h>
#include <Animation/Animation.h>
//#include "../JsonDataStructs.h"
#include "GameObjects/JsonDataStructs.h"
#include <CU\DLDebug\DL_Debug.h>
#include <PostMaster/SingletonPostMaster.h>
#include <Message/DijkstraMessage.h>
#include <Message/ActorPositionChangedMessage.h>
#include <Message/ColliderMessage.h>
#include <Message/PlayerReachedTargetMessage.h>

Actor::Actor()
{
	mySprite = new StaticSprite();
	myVelocity = CU::Vector2f::Zero;
	myAP = 5;
	myPath.Init(1);
	myCurrentWaypoint = 0;

	//myBoxCollider = new BoxCollider();
	//myBoxCollider->SetPositionAndSize(CU::Vector2f::One, CU::Vector2f::Half);
}

Actor::~Actor()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eMouseClicked, *this);
}

void Actor::Init(const ActorData &aActorData)
{
	myActiveFlag = true;
	myVisibleFlag = false;

	myPosition = CommonUtilities::Vector2f::Zero;
	myTargetPosition = CommonUtilities::Point2ui(myPosition);
	mySprite->Init();
	mySprite->SetLayer(enumRenderLayer::eGameObjects);
	mySprite->SetPivotWithPixels(CU::Vector2f(64.f, 32.f));
	myAnimations.Init(aActorData.myAnimations);

	myBoxCollider.SetPositionAndSize(myPosition, CU::Vector2f::Half);

	SingletonPostMaster::AddReciever(RecieverTypes::eMouseClicked, *this);
}

void Actor::UpdateDirection()
{
	if (myState == eActorState::eWalking)
	{
		if (myVelocity.x < 0.f && myVelocity.y < 0.f)
		{
			myDirection = eDirection::NORTH_WEST;
		}
		else if (myVelocity.x == 0.f && myVelocity.y < 0.f)
		{
			myDirection = eDirection::NORTH;
		}
		else if (myVelocity.x > 0.f && myVelocity.y < 0.f)
		{
			myDirection = eDirection::NORTH_EAST;
		}
		else if (myVelocity.x > 0.f && myVelocity.y == 0.f)
		{
			myDirection = eDirection::EAST;
		}
		else if (myVelocity.x > 0.f && myVelocity.y > 0.f)
		{
			myDirection = eDirection::SOUTH_EAST;
		}
		else if (myVelocity.x == 0.f && myVelocity.y > 0.f)
		{
			myDirection = eDirection::SOUTH;
		}
		else if (myVelocity.x < 0.f && myVelocity.y > 0.f)
		{
			myDirection = eDirection::SOUTH_WEST;
		}
		else if (myVelocity.x < 0.f && myVelocity.y == 0.f)
		{
			myDirection = eDirection::WEST;
		}
	}
}

void Actor::Update(const CU::Time& aDeltaTime)
{
	if (myActiveFlag == true)
	{

		myVelocity = (CommonUtilities::Point2f(myTargetPosition) - myPosition).GetNormalized() * 3.f;
		UpdatePosition(myPosition + (myVelocity * aDeltaTime.GetSeconds()));
		//myPosition += myVelocity * aDeltaTime.GetSeconds();
		CU::Vector2f distance = myVelocity * aDeltaTime.GetSeconds();
		if (myAnimations.GetIsActive() == true)
		{
			myAnimations.Update();
			mySprite = myAnimations.GetSprite();
			mySprite->SetLayer(enumRenderLayer::eGameObjects);
			mySprite->SetPivotWithPixels(CU::Vector2f(64.f, 32.f));
		}
		if ( (CommonUtilities::Point2f(myTargetPosition) - myPosition).Length() <= distance.Length())
		{
			myAtTarget = true;
			UpdatePosition(CU::Point2f(myTargetPosition));
			
			if (GetActorState() != eActorState::eFighting && GetActorState() != eActorState::eDead)
			{
				SetActorState(eActorState::eIdle);
			}
		}
		else
		{
			myAtTarget = false;
		}

		UpdatePath();
		UpdateDirection();
		DecideAnimation();
	}
}

void Actor::Draw() const
{
	if (myActiveFlag == true)
	{
		mySprite->Draw(myPosition);
		myBoxCollider.DrawCollider();
	}
}

void Actor::Move(CU::Vector2ui aTargetPosition)
{
	if (aTargetPosition != myTargetPosition)
	{
		OnMove(aTargetPosition);
	}
	myTargetPosition = aTargetPosition;
	SendPostMessage(PlayerChangedTargetMessage(RecieverTypes::ePlayerChangedTarget));
}

void Actor::OnMove(CU::Vector2ui aTargetPosition)
{

}

void Actor::SetPath(const CommonUtilities::GrowingArray<CommonUtilities::Vector2ui>& aPath)
{
	if (myCurrentWaypoint == myPath.Size())
	{
		myPath = aPath;
		myCurrentWaypoint = 0;
	}
}

void Actor::SetVisibleState(const bool aVisibleFlag)
{
	myVisibleFlag = aVisibleFlag;
}

bool Actor::GetVisibleState() const
{
	return myVisibleFlag;
}

int Actor::GetMyAP() const
{
	return myAP;
}

void Actor::UpdatePath()
{
	if (myAtTarget == true && myCurrentWaypoint < myPath.Size())
	{
		SetActorState(eActorState::eWalking);
		Move(myPath[myCurrentWaypoint]);
		++myCurrentWaypoint;
		if (myCurrentWaypoint == myPath.Size())
		{
			ReachedTarget();
		}
	}
}

void Actor::ChangeAnimation(const std::string& anAnimation)
{
	myAnimations.ChangeAnimation(anAnimation);
}

void Actor::AddAnimation(Animation* anAnimation)
{
	myAnimations.AddAnimation(anAnimation);
}

void Actor::StopPath()
{
	myCurrentWaypoint = myPath.Size();
}

void Actor::UpdatePosition(const CU::Vector2f & aPosition)
{
	myPosition = aPosition;
	myBoxCollider.ChangePosition(aPosition);
}

void Actor::DecideAnimation()
{

}

void Actor::RecieveMessage(const ColliderMessage & aMessage)
{
	if (myBoxCollider.CheckCollision(aMessage.myCollider) == true)
	{
		OnClick();
	}
}
