#include "stdafx.h"
#include "Animation.h"
#include "../CommonUtilities/CU/Timer/TimeManager.h"
#include <map>

void SetTextureRectangle(DX2D::CSprite* newSprite, const CU::Vector2f &aSpriteOffsetStart, const CU::Vector2f &aSpriteSize, bool aResizeSprite);
void UpdateSpriteSize(const CU::Vector2f &aSpriteSize, DX2D::CSprite* newSprite);
void ChangeAnimation(const std::string& anAnimation);

Animation::Animation()
{
	myName = "";
	mySpriteSheet = nullptr;
	mySpriteSize = CU::Vector2f(0, 0);
	myAmountOfColumns = 0;
	myAmountOfRows = 0;
	myAmountOfFrames = 0;
	myAnimationSpeed = 0;
	myIsLooping = false;

	myCurrentColumn = 0;
	myCurrentRow = 0;
	myCurrentFrame = 0;
	myAnimationTimer = 0.f;
	myIsRunning = false;

	myIsFirstFrame = false;
}

Animation::~Animation()
{
}

/*void Animation::InitializeAnimation(picojson::object& anAnimationObject)
{
	myName = JsonWrapper::GetString("Name", anAnimationObject);
	std::string animationSpriteSheet = JsonWrapper::GetString("SpriteSheet", anAnimationObject);
	mySpriteSheet = SpriteManager::GetInstance()->CreateSprite(animationSpriteSheet, SpriteManager::RenderLayer::Foreground);
	mySpriteSize = JsonWrapper::GetVector2f("FrameSize", anAnimationObject);
	myAmountOfColumns = JsonWrapper::GetInt("AmountOfColumns", anAnimationObject);
	myAmountOfRows = JsonWrapper::GetInt("AmountOfRows", anAnimationObject);
	myAmountOfFrames = JsonWrapper::GetInt("AmountOfFrames", anAnimationObject);
	myAnimationSpeed = JsonWrapper::GetInt("FramesPerSecond", anAnimationObject);
	myIsRunning = JsonWrapper::GetBool("StartRunning", anAnimationObject);
	myIsLooping = JsonWrapper::GetBool("ShouldLoop", anAnimationObject);
	myIsInteruptable = JsonWrapper::GetBool("IsInteruptable", anAnimationObject);
	myInTransition = JsonWrapper::GetString("InTransition", anAnimationObject);
	myOutTransition = JsonWrapper::GetString("OutTransition", anAnimationObject);

	myCurrentColumn = 1;
	myCurrentRow = 1;
	myCurrentFrame = 1;
	myAnimationTimer = 0.f;
	myHasPlayed = false;

	if (myIsRunning == false)
	{
		SpriteManager::GetInstance()->ShowOrHideBatch(mySpriteSheet, false);
		SpriteManager::GetInstance()->ShowOrHideSprite(mySpriteSheet, false);
	}
}*/

void Animation::UpdateAnimation()
{	
	if (myIsRunning == true)
	{
		myAnimationTimer += CU::TimeManager::GetDeltaTime().GetSeconds();

		if (myAnimationTimer >= 1.f / myAnimationSpeed)
		{
			if (myCurrentFrame < myAmountOfFrames - 1 || (myAmountOfFrames == 2 && myCurrentFrame < 2))
			{
				if (myIsFirstFrame == false)
				{
					myCurrentFrame++;
				}
				else
				{
					myIsFirstFrame = false;
				}

				if (myCurrentFrame >= myAmountOfColumns * myCurrentRow)
				{
					myCurrentRow++;
				}

				if (myCurrentColumn < myAmountOfColumns)
				{
					myCurrentColumn++;
				}
				else
				{
					myCurrentColumn = 1;
				}

				SetAnimationFrame();

			}
			else
			{
				if (myIsLooping == false || myShouldStop == true)
				{
					StopAnimation();
				}
				else
				{
					//This is what makes animations with 1 frame work.
					myCurrentColumn = 1;
					myCurrentRow = 1;
					myCurrentFrame = 1;
					myIsFirstFrame = true;
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
	myCurrentFrame = 1;
	myIsRunning = true;
	myShouldStop = false;
	myIsFirstFrame = true;
	SetHasPlayed(true);
	SetTextureRectangle(mySpriteSheet
		, CU::Vector2f(0.f, 0.f), CU::Vector2f(0.f, 0.f), true);
	//ShowSprite();
}

void Animation::StopAnimation()
{
	myCurrentColumn = 0;
	myCurrentRow = 0;
	myCurrentFrame = 0;
	myIsRunning = false;
	SetTextureRectangle(mySpriteSheet
		, CU::Vector2f(0.f, 0.f), CU::Vector2f(0.f, 0.f), true);
	//HideSprite();
}

void Animation::StopAnimationAtEnd()
{
	myShouldStop = true;
}

void SetTextureRectangle(DX2D::CSprite* newSprite, const CU::Vector2f &aSpriteOffsetStart,
	const CU::Vector2f &aSpriteSize, bool aResizeSprite)
{
	// Temps to make it easier to read and understand
	auto size = newSprite->GetImageSize();

	CU::Vector2f fixSize = aSpriteSize;

	// Start, in 0-1
	CU::Vector2f start(aSpriteOffsetStart.x / size.x,
		aSpriteOffsetStart.y / size.y);

	// Length, in 0-1
	CU::Vector2f length((start.x + fixSize.x) / size.x,
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

	newSprite->SetTextureRect(start.x, start.y, start.x + length.x, start.y + length.y);
	if (aResizeSprite == true)
	{
		UpdateSpriteSize(fixSize, newSprite);
	}
}

void UpdateSpriteSize(const CU::Vector2f &aSpriteSize, DX2D::CSprite* newSprite)
{
	DX2D::Vector2f newSize;
	auto size = newSprite->GetImageSize();
	// How big in 0-1 it is compared to original size, so using pixels
	newSize.x = aSpriteSize.x / (size.x);
	newSize.y = aSpriteSize.y / (size.y);

	newSprite->SetSize(newSize);
}

/*void ChangeAnimation(const std::string& anAnimation)
{
	if (myActiveAnimation != anAnimation)
	{
		if (myActiveAnimation != "")
		{
			if (myAnimations[myActiveAnimation]->GetIsRunning() == false || myAnimations[myActiveAnimation]->GetIsInteruptable() == true)
			{
				myAnimations[myActiveAnimation]->StopAnimation();
				if (myAnimations[myActiveAnimation]->GetInTransition() != "")
				{
					if (myAnimations[myAnimations[myActiveAnimation]->GetInTransition()]->GetHasPlayed() == true)
					{
						myAnimations[myAnimations[myActiveAnimation]->GetInTransition()]->SetHasPlayed(false);
					}
				}
				if (myAnimations[myActiveAnimation]->GetOutTransition() != "")
				{
					if (myAnimations[myAnimations[myActiveAnimation]->GetOutTransition()]->GetHasPlayed() == true)
					{
						myAnimations[myAnimations[myActiveAnimation]->GetOutTransition()]->SetHasPlayed(false);
					}
				}

				if (myAnimations[myActiveAnimation]->GetOutTransition() == "" ||
					myAnimations[myAnimations[myActiveAnimation]->GetOutTransition()]->GetHasPlayed() == true)
				{
					if (myAnimations[anAnimation]->GetInTransition() == "" ||
						myAnimations[myAnimations[anAnimation]->GetInTransition()]->GetHasPlayed() == true)
					{
						myActiveAnimation = anAnimation;
					}
					else if (myActiveAnimation != myAnimations[anAnimation]->GetInTransition())
					{
						myActiveAnimation = myAnimations[anAnimation]->GetInTransition();
						myAnimations[myActiveAnimation]->StopAnimationAtEnd();
					}
				}
				else if (myActiveAnimation != myAnimations[anAnimation]->GetOutTransition())
				{
					myActiveAnimation = myAnimations[myActiveAnimation]->GetOutTransition();
					myAnimations[myActiveAnimation]->StopAnimationAtEnd();
				}
				myAnimations[myActiveAnimation]->StartAnimation();
			}
			else
			{
				myAnimations[myActiveAnimation]->StopAnimationAtEnd();
			}
		}
		else
		{
			myActiveAnimation = anAnimation;
			myAnimations[myActiveAnimation]->StartAnimation();
		}
	}
}*/