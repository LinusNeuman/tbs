#pragma once
#include <map>
#include <Animation/AnimationHandler.h>
#include <Collision/BoxCollider.h>
#include <CU/Timer/Time.h>
#include <PostMaster/MessageReceiver.h>


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

enum class eActorState
{
	eIdle,
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
	void SetPath(const CommonUtilities::GrowingArray<CommonUtilities::Vector2ui>& aPath);

	void ChangeAnimation(const std::string& anAnimation);
	void AddAnimation(Animation* anAnimation);

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

	virtual void RecieveMessage(const ColliderMessage & aMessage) override;

	virtual void OnClick() = 0;

	void SetActiveState(const bool aActiveFlag);
	bool GetActiveState();

	

	virtual void ReachedTarget() = 0;
	virtual int GetMyAP() const;
	StaticSprite* GetSprite() const
	{
		return mySprite;
	}
	
protected:
	void UpdatePosition(const CU::Vector2f & aPosition);
	bool myActiveFlag;

	AnimationHandler myAnimations;
	virtual void DecideAnimation();
	CU::Vector2ui myTargetPosition;
	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	eActorState myState;
	int myAP;
	CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> myPath;
	unsigned short myCurrentWaypoint;

	BoxCollider myBoxCollider;

private:
	void UpdatePath();

	
	eActorType myType;
	
	StaticSprite *mySprite;
	bool myAtTarget;
};

inline void Actor::SetActiveState(const bool aActiveFlag)
{
	myActiveFlag = aActiveFlag;
}

inline bool Actor::GetActiveState()
{
	return myActiveFlag;
}
