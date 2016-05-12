#include "stdafx.h"
#include "Animation.h"
#include "../CommonUtilities/CU/Timer/TimeManager.h"
#include <map>

void SetTextureRectangle(WrappedSprite* newSprite, const CommonUtilities::Vector2f &aSpriteOffsetStart, const CommonUtilities::Vector2f &aSpriteSize, bool aResizeSprite, const CommonUtilities::Vector2f &aAnimationSize);
void UpdateSpriteSize(const CommonUtilities::Vector2f &aSpriteSize, WrappedSprite* newSprite, const CommonUtilities::Vector2f &aAnimationSize);
void ChangeAnimation(const std::string& anAnimation);

Animation::Animation()
{
	myName = "";
	//mySpriteSheet = nullptr;
	mySpriteSize = CommonUtilities::Vector2f(0, 0);
	myAmountOfColumns = 0;
	myAmountOfRows = 0;
	myAmountOfFrames = 0;
	myAnimationSpeed = 0;
	myShouldLoop = false;

	myCurrentColumn = 0;
	myCurrentRow = 0;
	myCurrentFrame = 0;
	myAnimationTimer = 0.f;
	myIsRunning = false;
}

Animation::~Animation()
{
}

void Animation::InitializeAnimation(picojson::object& anAnimationObject)
{
	myName = JsonWrapper::GetString("Name", anAnimationObject);
	std::string animationSpriteSheet = JsonWrapper::GetString("FilePath", anAnimationObject);
	mySpriteSheet.Init(animationSpriteSheet.c_str());
	mySpriteSize = CU::Vector2f(static_cast<float>(JsonWrapper::GetInt("SizeX", anAnimationObject))
		, static_cast<float>(JsonWrapper::GetInt("SizeY", anAnimationObject)));
	myAmountOfColumns = JsonWrapper::GetInt("AmountOfColumns", anAnimationObject);
	myAmountOfRows = JsonWrapper::GetInt("AmountOfRows", anAnimationObject);
	myAmountOfFrames = JsonWrapper::GetInt("AmountOfFrames", anAnimationObject);
	myAnimationSpeed = JsonWrapper::GetInt("AnimationSpeed", anAnimationObject);
	myLoopStartFrame = JsonWrapper::GetInt("LoopStart", anAnimationObject);
	myLoopEndFrame = JsonWrapper::GetInt("LoopEnd", anAnimationObject);
	myShouldLoop = JsonWrapper::GetBool("ShouldLoop", anAnimationObject);
	myIsInteruptable = JsonWrapper::GetBool("IsInterruptible", anAnimationObject);
	myInTransition = JsonWrapper::GetString("InTransition", anAnimationObject);
	myOutTransition = JsonWrapper::GetString("OutTransition", anAnimationObject);

	myCurrentColumn = 1;
	myCurrentRow = 1;
	myCurrentFrame = 0;
	myAnimationTimer = 0.f;
	myHasPlayed = false;
	myIsRunning = true;
}

void Animation::UpdateAnimation()
{	
	if (myIsRunning == true)
	{
		myAnimationTimer += CommonUtilities::TimeManager::GetDeltaTime().GetSeconds();

		if (myAnimationTimer >= 1.f / myAnimationSpeed)
		{
			if ((myHasPlayed == false && myCurrentFrame < myAmountOfFrames - 1)
				|| (myHasPlayed == true && myCurrentFrame < myLoopEndFrame - 1))
			{
				myCurrentFrame++;
				myCurrentRow = myCurrentFrame / myAmountOfColumns + 1;
				myCurrentColumn = myCurrentFrame - myAmountOfColumns * (myCurrentRow - 1);
				SetAnimationFrame();
			}
			else
			{
				if (myShouldLoop == false || myShouldStop == true)
				{
					StopAnimation();
				}
				else
				{
					myHasPlayed = true;
					myCurrentFrame = myLoopStartFrame - 1;
					myCurrentRow = myCurrentFrame / myAmountOfColumns + 1;
					myCurrentColumn = myCurrentFrame - myAmountOfColumns * (myCurrentRow - 1);
					SetAnimationFrame();
				}
			}
			myAnimationTimer = 0.f;
		}
		else
		{
			SetAnimationFrame();
		}
	}
}

void Animation::StartAnimation()
{
	myCurrentColumn = 1;
	myCurrentRow = 1;
	myCurrentFrame = 0;
	myIsRunning = true;
	myShouldStop = false;
	SetHasPlayed(true);
	SetTextureRectangle(&mySpriteSheet
		, CommonUtilities::Vector2f(0.f, 0.f), CommonUtilities::Vector2f(0.f, 0.f), true, CU::Vector2f(static_cast<float>(myAmountOfColumns), static_cast<float>(myAmountOfRows)));
	//ShowSprite();
}

void Animation::StopAnimation()
{
	myCurrentColumn = 0;
	myCurrentRow = 0;
	myCurrentFrame = 0;
	myIsRunning = false;
	SetTextureRectangle(&mySpriteSheet
		, CommonUtilities::Vector2f(0.f, 0.f), CommonUtilities::Vector2f(0.f, 0.f), true, CU::Vector2f(static_cast<float>(myAmountOfColumns), static_cast<float>(myAmountOfRows)));
	//HideSprite();
}

void Animation::StopAnimationAtEnd()
{
	myShouldStop = true;
}

void Animation::SetAnimationFrame()
{
	SetTextureRectangle(&mySpriteSheet, CommonUtilities::Vector2f(static_cast<float>(myCurrentColumn)* mySpriteSize.x, (myCurrentRow - 1) * mySpriteSize.y), mySpriteSize, true, CU::Vector2f(static_cast<float>(myAmountOfColumns), static_cast<float>(myAmountOfRows)));
}

void SetTextureRectangle(WrappedSprite* newSprite, const CommonUtilities::Vector2f &aSpriteOffsetStart,
	const CommonUtilities::Vector2f &aSpriteSize, bool aResizeSprite, const CommonUtilities::Vector2f &aAnimationSize)
{
	// Temps to make it easier to read and understand
	auto size = newSprite->GetSprite()->GetImageSize();

	CommonUtilities::Vector2f fixSize = aSpriteSize;

	// Start, in 0-1
	CommonUtilities::Vector2f start(aSpriteOffsetStart.x / size.x,
		aSpriteOffsetStart.y / size.y);

	// Length, in 0-1
	CommonUtilities::Vector2f length((start.x + fixSize.x) / size.x,
		(start.y + fixSize.y) / size.y);

	if (aSpriteOffsetStart.x > 1024.f)
	{
		length.x = floor(((length.x) * 2000));
		length.x = length.x / 2000;
	}

	if (aSpriteOffsetStart.y > 1024.f)
	{
		length.y = floor(((length.y) * 2500));
		length.y = length.y / 2500;
	};

	newSprite->GetSprite()->SetTextureRect(start.x, start.y, start.x + length.x, start.y + length.y);
	if (aResizeSprite == true)
	{
		UpdateSpriteSize(fixSize, newSprite, CommonUtilities::Vector2f(aAnimationSize.x, aAnimationSize.y));
	}
}

void UpdateSpriteSize(const CommonUtilities::Vector2f &aSpriteSize, WrappedSprite* newSprite, const CommonUtilities::Vector2f &aAnimationSize)
{
	DX2D::Vector2f newSize;
	auto size = newSprite->GetSprite()->GetImageSize();
	// How big in 0-1 it is compared to original size, so using pixels
	newSize.x = aSpriteSize.x / (size.x * aAnimationSize.y);
	newSize.y = aSpriteSize.y / (size.y * aAnimationSize.x);

	newSprite->GetSprite()->SetSize(newSize);
}