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

	for (int i = 0; i <= 5; ++i)
	{
		myStepSounds[i] = new SoundEffect();
	}
	myStepSounds[0]->Init("Sounds/SFX/step1.ogg");
	myStepSounds[1]->Init("Sounds/SFX/step2.ogg");
	myStepSounds[2]->Init("Sounds/SFX/step3.ogg");
	myStepSounds[3]->Init("Sounds/SFX/step4.ogg");
	myStepSounds[4]->Init("Sounds/SFX/step5.ogg");
	myStepSounds[5]->Init("Sounds/SFX/step6.ogg");

	for (int i = 0; i <= 4; ++i)
	{
		myFightSounds[i] = new SoundEffect();
	}

	myFightSounds[0]->Init("Sounds/SFX/hit1.ogg");
	myFightSounds[1]->Init("Sounds/SFX/hit2.ogg");
	myFightSounds[2]->Init("Sounds/SFX/hit3.ogg");
	myFightSounds[3]->Init("Sounds/SFX/hit4.ogg");
	myFightSounds[4]->Init("Sounds/SFX/hit5.ogg");

	myBonus = new SoundEffect();
	myBonus->Init("Sounds/SFX/clownhorn.ogg");

	myFightTimer = 0.0f;
	myStepTimer = 0.0f;
}

Actor::~Actor()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eMouseClicked, *this);

	for (int i = 0; i <= 5; ++i)
	{
		myStepSounds[i] = nullptr;
		delete myStepSounds[i];
	}

	for (int i = 0; i <= 4; ++i)
	{
		myFightSounds[i] = nullptr;
		delete myFightSounds[i];
	}
}

void Actor::Init(const ActorData &aActorData)
{
	myActiveFlag = true;
	myVisibleFlag = false;
	myType = aActorData.myActortype;
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
	myPreviousDirection = myDirection;
	if (myState == eActorState::eWalking)
	{
		CU::Vector2f direction = CU::Vector2f(myTargetPosition) - myPosition;
		if (direction.x < 0.f && direction.y < 0.f)
		{
			myDirection = eDirection::NORTH_WEST;
		}
		else if (direction.x == 0.f && direction.y < 0.f)
		{
			myDirection = eDirection::NORTH;
		}
		else if (direction.x > 0.f && direction.y < 0.f)
		{
			myDirection = eDirection::NORTH_EAST;
		}
		else if (direction.x > 0.f && direction.y == 0.f)
		{
			myDirection = eDirection::EAST;
		}
		else if (direction.x > 0.f && direction.y > 0.f)
		{
			myDirection = eDirection::SOUTH_EAST;
		}
		else if (direction.x == 0.f && direction.y > 0.f)
		{
			myDirection = eDirection::SOUTH;
		}
		else if (direction.x < 0.f && direction.y > 0.f)
		{
			myDirection = eDirection::SOUTH_WEST;
		}
		else if (direction.x < 0.f && direction.y == 0.f)
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
			myStepTimer += aDeltaTime.GetSeconds();
			if (myStepTimer >= 0.4f)
			{
				int step = (rand() % 6);
				myStepSounds[step]->Play(0.4f);
				myStepTimer = 0.f;
			}

			myVelocity = (CommonUtilities::Point2f(myTargetPosition) - myPosition).GetNormalized() * 3.f;
			UpdatePosition(myPosition + (myVelocity * aDeltaTime.GetSeconds()));
			CU::Vector2f distance = myVelocity * aDeltaTime.GetSeconds();
			if ((CU::Point2f(myTargetPosition) - myPosition).Length() <= distance.Length())
			{
				myAtTarget = true;
				UpdatePosition(CU::Point2f(myTargetPosition));
				

				if (GetActorState() != eActorState::eFighting && GetActorState() != eActorState::eDead && GetActorState() != eActorState::eAlert)
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
			myFightTimer += aDeltaTime.GetSeconds();

			if (myFightTimer >= 0.07f)
			{
				int fight = (rand() % 150);
				if (fight == 0)
				{
					myBonus->Play(0.4f);
				}
				else
				{
					fight /= 30;
					myFightSounds[fight]->Play(0.4f);

				}

				myFightTimer = 0.f;
			}
			if (myAnimations.GetAnimationIsRunning() == false)
			{
				SetActorState(eActorState::eDead);
			}
		}

		if (myAnimations.GetIsActive() == true)
		{
			myAnimations.Update(aDeltaTime);
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
	UpdateDirection();
}

void Actor::OnMove(CU::Vector2ui aTargetPosition)
{

}

void Actor::AfterTurn()
{
	ResetObjectiveState();
	myStepTimer = 0.0f;
	myFightTimer = 0.0f;
}

void Actor::ResetObjectiveState()
{
	myHasObjectiveFlag = false;
	myObjectiveTargetPosition = TilePositionf::Zero;
}

void Actor::ReachedWaypoint()
{
	
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
			ReachedWaypoint();

			if (myCurrentWaypoint == myPath.Size())
			{
				AlmostReachTarget();
			}
		}
		else if (myCurrentWaypoint == myPath.Size())
		{
			ReachedWaypoint();
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

void Actor::StopPath()
{
	myCurrentWaypoint = myPath.Size();
}

void Actor::SetPreviousPosition(const TilePositionf& aPosition)
{
	myPreviousPosition = aPosition;
}

TilePositionf Actor::GetPreviousPosition() const
{
	return myPreviousPosition;
}

void Actor::UpdatePosition(const CU::Vector2f & aPosition)
{
	myPosition = aPosition;
	myBoxCollider.ChangePosition(aPosition);
}

void Actor::DecideAnimation()
{

}

eDirection Actor::GetPreviousDirectionEnum() const
{
	return myPreviousDirection;
}

bool Actor::RecieveMessage(const ColliderMessage & aMessage)
{
	if (myBoxCollider.CheckCollision(aMessage.myCollider) == true)
	{
		OnClick();
	}
	return true;
}
