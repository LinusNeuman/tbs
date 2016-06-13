#pragma once
#include <map>
#include <Animation/AnimationHandler.h>
#include <Collision/BoxCollider.h>
#include <CU/Timer/Time.h>
#include <PostMaster/MessageReceiver.h>
#include <CU/Utility/GameSpecificTypeDefs.h>
#include <ActorEnums.h>


struct ActorData;
class StaticSprite;
class Animation;
class BoxCollider;

class Actor : public MessageReciever
{
public:
	Actor();
	virtual ~Actor();
	void Init(const ActorData &aActorData);
	void SpriteInit();

	virtual void Update(const CU::Time &aDeltaTime);
	virtual void Draw() const;
	void Move(CU::Vector2ui aTargetPosition);
	virtual void OnMove(CU::Vector2ui aTargetPosition);
	virtual void AfterTurn();

	virtual void NextToObjective();
	//virtual void OnObjective();

	void SetPath(const PathArray & aPath);

	void ChangeAnimation(const std::string& anAnimation);

	void StopPath();

	void SetPosition(const CommonUtilities::Vector2f & aPos)
	{
		UpdatePosition(aPos);
		myTargetPosition = CommonUtilities::Vector2ui(aPos);
	}
	void SetPreviousPosition(const TilePositionf& aPosition);
	
	CU::Vector2f GetPosition() const
	{
		return myPosition;
	}
	TilePositionf GetPreviousPosition() const;

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
	eDirection GetPreviousDirectionEnum() const;

	virtual bool RecieveMessage(const ColliderMessage & aMessage) override;

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
	TilePositionf myPreviousPosition;
	CU::Vector2f myVelocity;

	eActorState myState;
	int myAP;
	PathArray myPath;
	unsigned short myCurrentWaypoint;

	BoxCollider myBoxCollider;
	void UpdateDirection();
	bool myAtTarget;
	eDirection myDirection;
	eDirection myPreviousDirection;
	StaticSprite *mySprite;
	bool myIsSeen;
private:
	void UpdatePath();

	eActorType myType;
	
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
