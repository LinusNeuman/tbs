#include "stdafx.h"
#include "Animation.h"
#include <CU/Timer/TimeManager.h>
#include <map>
#include <tga2d/sprite/sprite.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

void SetTextureRectangle(StaticSprite* newSprite, const CommonUtilities::Vector2f &aSpriteOffsetStart, const CommonUtilities::Vector2f &aSpriteSize, bool aResizeSprite);

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
		, CommonUtilities::Vector2f(0.f, 0.f), mySpriteSize, true);
	//ShowSprite();
}

void Animation::StopAnimation()
{
	myCurrentColumn = 0;
	myCurrentRow = 0;
	myCurrentFrame = 0;
	myIsRunning = false;
	SetTextureRectangle(&mySpriteSheet
		, CommonUtilities::Vector2f(0.f, 0.f), CommonUtilities::Vector2f(0.f, 0.f), true);
	//HideSprite();
}

void Animation::StopAnimationAtEnd()
{
	myShouldStop = true;
}

void Animation::SetAnimationFrame()
{
	SetTextureRectangle(&mySpriteSheet, CommonUtilities::Vector2f(static_cast<float>(myCurrentColumn)* mySpriteSize.x, (myCurrentRow - 1) * mySpriteSize.y), mySpriteSize, true);
}

/*
	MINA SYSTEM FUCKAR ALRDIG UPP //LEON
*/
void SetTextureRectangle(StaticSprite* newSprite, const CommonUtilities::Vector2f &aSpriteOffsetStart,
	const CommonUtilities::Vector2f &aSpriteSize, bool aResizeSprite)
{
	const float spriteWidth = static_cast<float>(newSprite->GetSprite()->GetImageSize().x);
	const float spriteHeight = static_cast<float>(newSprite->GetSprite()->GetImageSize().y);

	const float TempStartPointX = aSpriteOffsetStart.x / spriteWidth;
	const float TempStartPointY = aSpriteOffsetStart.y / spriteHeight;

	const float TempWidth = aSpriteSize.x / spriteWidth;
	const float TempHeight = aSpriteSize.y / spriteHeight;

	const float TempEndPointX = TempStartPointX + TempWidth;
	const float TempEndPointY = TempStartPointY + TempHeight;

	newSprite->GetSprite()->SetTextureRect(TempStartPointX, TempStartPointY, TempEndPointX, TempEndPointY);

	float normalizedWindowSizeX = newSprite->GetSprite()->GetImageSize().x / FLOATCAST(SingletonDataHolder::GetTargetResolution().x) * (16.f / 9.f);
	float normalizedWindowSizeY = newSprite->GetSprite()->GetImageSize().y / FLOATCAST(SingletonDataHolder::GetTargetResolution().y);

	//newSprite->GetSprite()->SetSize(DX2D::Vector2f(normalizedWindowSizeX * TempWidth, normalizedWindowSizeY * TempHeight));
	newSprite->myRenderData.mySize = CU::Vector2f(normalizedWindowSizeX * TempWidth, normalizedWindowSizeY * TempHeight);
}