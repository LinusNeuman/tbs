#pragma once
#include <map>
#include "../Renderer/Animation/AnimationHandler.h"
#include <CU/Timer/Time.h>

struct ActorData;
class StaticSprite;
class Animation;

enum class eActorType
{
	ePlayerOne,
	ePlayerTwo,
	eEnemyOne,
	eEnemyTwo
};

enum class eActorState
{
	eIdle,
	eWalking
};

class Actor
{
public:
	Actor();
	~Actor();
	void Init(const ActorData &aActorData);
	virtual void Update(const CU::Time &aDeltaTime);
	void Draw() const;
	void Move(CU::Vector2ui aTargetPosition);
	void SetPath(CommonUtilities::GrowingArray<CommonUtilities::Vector2ui>);

	void ChangeAnimation(const std::string& anAnimation);
	void AddAnimation(Animation* anAnimation);
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

	int GetMyAP() const;
	StaticSprite *mySprite;
	
protected:
	StaticSprite* GetSprite() const
	{
		return mySprite;
	}
	AnimationHandler myAnimations;
	virtual void DecideAnimation();
	CU::Vector2ui myTargetPosition;
	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	eActorState myState;
private:
	void UpdatePath();

	CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> myPath;
	unsigned short myCurrentWaypoint;
	eActorType myType;
	int myAP;

	bool myAtTarget;
};

