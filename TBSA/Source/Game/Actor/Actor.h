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
	void Init(ActorData aActorData);
	void Update(const CU::Time &aDeltaTime);
	void Draw() const;
	void Move(CU::Vector2f aTargetPosition);
	void ChangeAnimation(const std::string& anAnimation);
	void AddAnimation(Animation* anAnimation);
	CU::Vector2f GetPosition() const
	{
		return myPosition;
	}
	eActorType GetType() const
	{
		return myType;
	}
protected:
	StaticSprite* GetSprite() const
	{
		return mySprite;
	}
	std::map<std::string, Animation*> myAnimations;
	std::string myActiveAnimation;
private:
	StaticSprite *mySprite;
	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	CU::Vector2f myTargetPosition;
	eActorType myType;
};

