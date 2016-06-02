#pragma once
#include <map>
#include <Animation/AnimationHandler.h>
#include <Collision/BoxCollider.h>
#include <CU/Timer/Time.h>
#include <PostMaster/MessageReceiver.h>
#include <CU/Utility/GameSpecificTypeDefs.h>



struct ActorData;
class StaticSprite;
class Animation;
class BoxCollider;

enum class eActorType
{
	ePlayerOne,
	ePlayerTwo,
	eEnemyOne,
	eEnemyTwo,
	eEnemyThree,
	eEnemyFour,
	eEnemyFive
};

enum class eDirection
{
	NORTH = 50,
	NORTH_EAST = 40,
	EAST = 30,
	SOUTH_EAST = 20,
	SOUTH = 10,
	SOUTH_WEST = 80,
	WEST = 70,
	NORTH_WEST = 60
};

enum class eActorState
{
	eIdle,
	eFighting,
	eDead,
	eWalking
};

class Actor : public MessageReciever
{
public:
	Actor();
	virtual ~Actor();
	void Init(const ActorData &aActorData);
	
	virtual void Update(const CU::Time &aDeltaTime);
	void Draw() const;
	void Move(CU::Vector2ui aTargetPosition);
	virtual void OnMove(CU::Vector2ui aTargetPosition);
	virtual void AfterTurn();
	void SetPath(const PathArray & aPath);

	void ChangeAnimation(const std::string& anAnimation);
	void AddAnimation(Animation* anAnimation);

	void StopPath();

	void SetPosition(const CommonUtilities::Vector2f & aPos)
	{
		UpdatePosition(aPos);
		myTargetPosition = CommonUtilities::Vector2ui(aPos);
	}
	
	
	CU::Vector2f GetPosition() const
	{
		return myPosition;
	}


	CU::Vector2f GetDirection() const
	{
		return myVelocity.GetNormalized();
	}
	eActorType GetType() const
	{
		return myType;
	}

	eDirection GetDirectionEnum() const
	{
		return myDirection;
	}

	virtual void RecieveMessage(const ColliderMessage & aMessage) override;

	virtual void OnClick() = 0;

	void SetActorState(const eActorState aActorState);
	eActorState GetActorState();

	void SetActiveState(const bool aActiveFlag);
	bool GetActiveState();
	void SetVisibleState(const bool aVisibleFlag);
	bool GetVisibleState() const;
	CU::Vector2ui GetTargetPosition() const
	{
		return myTargetPosition;
	}

	virtual void AlmostReachTarget() = 0;
	virtual void ReachedTarget() = 0;
	virtual int GetMyAP() const;
	StaticSprite* GetSprite() const
	{
		return mySprite;
	}
	
	void SetObjective(const TilePositionf & aPosition);
	void ResetObjectiveState();
	const TilePositionf & GetObjectiveTargetPosition();

protected:
	bool GetObjectiveState();

	void UpdatePosition(const CU::Vector2f & aPosition);
	bool myActiveFlag;
	bool myVisibleFlag;
	bool myHasObjectiveFlag;

	AnimationHandler myAnimations;
	virtual void DecideAnimation();

	TilePositionf myObjectiveTargetPosition;

	TilePosition myTargetPosition;
	TilePositionf myPosition;
	CU::Vector2f myVelocity;

	eActorState myState;
	int myAP;
	PathArray myPath;
	unsigned short myCurrentWaypoint;

	BoxCollider myBoxCollider;
	void UpdateDirection();
	bool myAtTarget;
	
private:
	void UpdatePath();

	eActorType myType;
	eDirection myDirection;
	StaticSprite *mySprite;
};

inline void Actor::SetActiveState(const bool aActiveFlag)
{
	myActiveFlag = aActiveFlag;
}

inline bool Actor::GetActiveState()
{
	return myActiveFlag;
}

inline void Actor::SetActorState(const eActorState aActorState)
{
	myState = aActorState;
}

inline eActorState Actor::GetActorState()
{
	return myState;
}

inline const TilePositionf & Actor::GetObjectiveTargetPosition()
{
	return myObjectiveTargetPosition;
}

inline void Actor::SetObjective(const TilePositionf & aPosition)
{
	myHasObjectiveFlag = true;
	myObjectiveTargetPosition = aPosition;
}

inline void Actor::ResetObjectiveState()
{
	myHasObjectiveFlag = false;
	myObjectiveTargetPosition = TilePositionf::Zero;
}

inline bool Actor::GetObjectiveState()
{
	return myHasObjectiveFlag;
}