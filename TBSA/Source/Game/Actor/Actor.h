#pragma once
#include <map>

class WrappedSprite;
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
	void Init(const CU::Vector2f &aStartPosition, const eActorType &aActorType);
	void SetSelected(const bool aValue);
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
	WrappedSprite* GetSprite() const
	{
		return mySprite;
	}
	std::map<std::string, Animation*> myAnimations;
	std::string myActiveAnimation;
private:
	WrappedSprite *mySprite;
	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	CU::Vector2f myTargetPosition;
	eActorType myType;
};

