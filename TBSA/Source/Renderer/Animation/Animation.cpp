#include "stdafx.h"
#include "Animation.h"
#include <CU/Timer/TimeManager.h>
#include <map>
#include <tga2d/sprite/sprite.h>



void SetTextureRectangle(StaticSprite* newSprite, const CommonUtilities::Vector2f &aSpriteOffsetStart, const CommonUtilities::Vector2f &aSpriteSize, bool aResizeSprite, const CommonUtilities::Vector2f &aAnimationSize);
void UpdateSpriteSize(const CommonUtilities::Vector2f &aSpriteSize, StaticSprite* newSprite, const CommonUtilities::Vector2f &aAnimationSize);
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

void SetTextureRectangle(StaticSprite* newSprite, const CommonUtilities::Vector2f &aSpriteOffsetStart,
	const CommonUtilities::Vector2f &aSpriteSize, bool aResizeSprite, const CommonUtilities::Vector2f &aAnimationSize)
{
	DX2D::Vector2f imageSize(newSprite->GetSprite()->GetImageSize().x, newSprite->GetSprite()->GetImageSize().y);
	newSprite->GetSprite()->SetTextureRect(aSpriteOffsetStart.x / imageSize.x, aSpriteOffsetStart.y / imageSize.y, (aSpriteOffsetStart.x + aSpriteSize.x) / imageSize.x, (aSpriteOffsetStart.y + aSpriteSize.y) / imageSize.y);
	DX2D::Vector2f newSize;
	newSize.x = aSpriteSize.x / DX2D::CEngine::GetInstance()->GetWindowSize().x;
	newSize.y = aSpriteSize.y / (DX2D::CEngine::GetInstance()->GetWindowSize().y * (16.f/9.f));
	newSprite->GetSprite()->SetSize(newSize);
}

void UpdateSpriteSize(const CommonUtilities::Vector2f &aSpriteSize, StaticSprite* newSprite, const CommonUtilities::Vector2f &aAnimationSize)
{
	DX2D::Vector2f newSize;
	auto size = newSprite->GetSprite()->GetImageSize();
	// How big in 0-1 it is compared to original size, so using pixels
	newSize.x = aSpriteSize.x / (size.x * aAnimationSize.y);
	newSize.y = aSpriteSize.y / (size.y * aAnimationSize.x);

	newSprite->GetSprite()->SetSize(newSize);
}