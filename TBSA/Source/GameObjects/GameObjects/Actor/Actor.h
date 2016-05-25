#pragma once
#include <map>

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

class Actor
{
public:
	Actor();
	~Actor();
	void Init(const ActorData &aActorData);
	void Update(const CU::Time &aDeltaTime);
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
	std::map<std::string, Animation*> myAnimations;
	std::string myActiveAnimation;
	
private:
	void UpdatePath();

	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	CU::Vector2ui myTargetPosition;
	CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> myPath;
	unsigned short myCurrentWaypoint;
	eActorType myType;
	int myAP;

	bool myAtTarget;
};

