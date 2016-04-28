#pragma once
#include "tga2d/sprite/sprite.h"
#include "../CommonUtilities/CU/Vectors/vector2.h"
//#include "../JsonWrapper/JsonWrapper.h"

class Animation
{
public:
	Animation();
	~Animation();
	//void InitializeAnimation(picojson::object& anAnimationObject);
	void UpdateAnimation();
	void StartAnimation();
	void StopAnimation();
	void StopAnimationAtEnd();
	void SetAnimationFrame();

	inline std::string& GetName();
	inline std::string& GetInTransition();
	inline std::string& GetOutTransition();
	inline DX2D::CSprite* GetSprite();
	inline CU::Vector2f GetFrameSize() const;
	inline CU::Vector2f GetSpriteGrid() const;
	inline bool GetIsRunning() const;
	inline bool GetIsInteruptable() const;
	inline bool GetHasPlayed() const;
	inline void SetHasPlayed(bool aHasPlayed);
private:
	std::string myInTransition;
	std::string myOutTransition;
	std::string myName;
	DX2D::CSprite* mySpriteSheet;
	CU::Vector2f mySpriteSize;
	int myAmountOfColumns;
	int myAmountOfRows;
	int myAmountOfFrames;
	int myCurrentColumn;
	int myCurrentRow;
	int myCurrentFrame;
	int myAnimationSpeed;
	bool myIsLooping;

	bool myHasPlayed;
	bool myIsRunning;
	bool myShouldStop;
	bool myIsInteruptable;
	bool myIsFirstFrame;
	float myAnimationTimer;
};

std::string& Animation::GetName()
{
	return myName;
}

std::string& Animation::GetInTransition()
{
	return myInTransition;
}

std::string& Animation::GetOutTransition()
{
	return myOutTransition;
}

DX2D::CSprite* Animation::GetSprite()
{
	return mySpriteSheet;
}

CU::Vector2f Animation::GetFrameSize() const
{
	return mySpriteSize;
}

CU::Vector2f Animation::GetSpriteGrid() const
{
	return CU::Vector2f(CU::Vector2i(myAmountOfColumns, myAmountOfRows));
}

bool Animation::GetIsRunning() const
{
	return myIsRunning;
}

bool Animation::GetIsInteruptable() const
{
	return myIsInteruptable;
}

bool Animation::GetHasPlayed() const
{
	return myHasPlayed;
}

void Animation::SetHasPlayed(bool aHasPlayed)
{
	myHasPlayed = aHasPlayed;
}