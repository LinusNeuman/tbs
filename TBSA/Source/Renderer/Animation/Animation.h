#pragma once
#include <CU/Vectors/vector2.h>
#include <JsonWrapper/JsonWrapper.h>
#include <Rend/StaticSprite.h>

namespace CommonUtilities{
	class Time;
}

class Animation
{
public:
	Animation();
	~Animation();
	void InitializeAnimation(picojson::object& anAnimationObject);
	void UpdateAnimation(CommonUtilities::Time aDeltaTime);
	void StartAnimation();
	void StopAnimation();
	void StopAnimationAtEnd();
	void SetAnimationFrame();

	inline std::string& GetName();
	inline std::string& GetInTransition();
	inline std::string& GetOutTransition();
	inline StaticSprite* GetSprite();
	inline CommonUtilities::Vector2f GetFrameSize() const;
	inline CommonUtilities::Vector2f GetSpriteGrid() const;
	inline bool GetIsRunning() const;
	inline bool GetIsInteruptable() const;
	inline bool GetHasPlayed() const;
	inline void SetHasPlayed(bool aHasPlayed);
	inline void Render();
private:
	std::string myInTransition;
	std::string myOutTransition;
	std::string myName;
	StaticSprite mySpriteSheet;
	CommonUtilities::Vector2f mySpriteSize;
	int myAmountOfColumns;
	int myAmountOfRows;
	int myAmountOfFrames;
	int myCurrentColumn;
	int myCurrentRow;
	int myCurrentFrame;
	int myAnimationSpeed;
	int myLoopStartFrame;
	int myLoopEndFrame;
	bool myShouldLoop;

	bool myHasPlayed;
	bool myIsRunning;
	bool myShouldStop;
	bool myIsInteruptable;
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

StaticSprite* Animation::GetSprite()
{
	return &mySpriteSheet;
}

CommonUtilities::Vector2f Animation::GetFrameSize() const
{
	return mySpriteSize;
}

CommonUtilities::Vector2f Animation::GetSpriteGrid() const
{
	return CommonUtilities::Vector2f(CommonUtilities::Vector2i(myAmountOfColumns, myAmountOfRows));
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

void Animation::Render()
{
	mySpriteSheet.Draw(CU::Vector2f(10.f, 5.f));
}