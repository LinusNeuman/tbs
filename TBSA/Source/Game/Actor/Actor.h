#pragma once

class WrappedSprite;


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
	Actor(const CU::Vector2f &aStartPosition, const eActorType &aActorType);
	~Actor();
	void SetSelected(const bool aValue);
	void Update(const CU::Time &aDeltaTime);
	void Draw() const;
	void Move(CU::Vector2f aTargetPosition, const CU::Time aDeltaTime);
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
private:
	WrappedSprite *mySprite;
	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	CU::Vector2f myTargetPosition;
	eActorType myType;
};

