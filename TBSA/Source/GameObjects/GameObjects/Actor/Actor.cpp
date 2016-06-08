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
#include <Message/ColliderMessage.h>
#include <Message/EnemyPositionChangedMessage.h>

Actor::Actor()
{
	mySprite = new StaticSprite();
	myVelocity = CU::Vector2f::Zero;
	myAP = 5;
	myPath.Init(1);
	myCurrentWaypoint = 0;
	myState = eActorState::eWalking;
	myHasObjectiveFlag = false;
	myObjectiveTargetPosition = TilePositionf::One;
	myDirection = eDirection::SOUTH;
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

void Actor::SpriteInit()
{

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
		eActorState tempState = GetActorState();
		if (tempState == eActorState::eWalking)
		{
			myVelocity = (CommonUtilities::Point2f(myTargetPosition) - myPosition).GetNormalized() * 3.f;
			UpdatePosition(myPosition + (myVelocity * aDeltaTime.GetSeconds()));
			CU::Vector2f distance = myVelocity * aDeltaTime.GetSeconds();
			
			if ((CU::Point2f(myTargetPosition) - myPosition).Length() <= distance.Length())
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
		}
		else if (tempState == eActorState::eFighting)
		{
			if (myAnimations.GetAnimationIsRunning() == false)
			{
				SetActorState(eActorState::eDead);
			}
		}

		if (myAnimations.GetIsActive() == true)
		{
			myAnimations.Update();
			mySprite = myAnimations.GetSprite();
			mySprite->SetLayer(enumRenderLayer::eGameObjects);
			mySprite->SetPivotWithPixels(CU::Vector2f(64.f, 32.f));
		}

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
}

void Actor::OnMove(CU::Vector2ui aTargetPosition)
{

}

void Actor::AfterTurn()
{
	ResetObjectiveState();
}

void Actor::NextToObjective()
{

}

void Actor::SetPath(const CommonUtilities::GrowingArray<CommonUtilities::Vector2ui>& aPath)
{
	if (myCurrentWaypoint == myPath.Size())
	{
		SetActorState(eActorState::eWalking);
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
 	if (myAtTarget == true )
	{
		if (myCurrentWaypoint < myPath.Size())
		{
			SetActorState(eActorState::eWalking);
			Move(myPath[myCurrentWaypoint]);
			++myCurrentWaypoint;
			if (myCurrentWaypoint == myPath.Size())
			{
				AlmostReachTarget();
			}
		}
		else if (myCurrentWaypoint == myPath.Size())
		{
			if (GetObjectiveState() == true && (myPosition - myObjectiveTargetPosition).Length() <= 1.f)
			{
				NextToObjective();
			}
			else
			{
				ReachedTarget();
			}
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

bool Actor::RecieveMessage(const ColliderMessage & aMessage)
{
	if (myBoxCollider.CheckCollision(aMessage.myCollider) == true)
	{
		OnClick();
	}
	return true;
}
