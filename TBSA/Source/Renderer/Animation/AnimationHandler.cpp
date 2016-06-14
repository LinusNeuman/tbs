#include "stdafx.h"
#include "AnimationHandler.h"
//#include "../GameObjects/GameObjects/Actor/Actor.h"

AnimationHandler::AnimationHandler()
{
}


AnimationHandler::~AnimationHandler()
{
	/*for (auto animations : myAnimations)
	{
		delete(animations.second);
	}*/
}

void AnimationHandler::Init(/*Actor* aHolder,*/ std::map<std::string, Animation> someAnimations)
{
	myAnimations = someAnimations;
}

void AnimationHandler::Update(CommonUtilities::Time aDeltaTime)
{
	myAnimations[myActiveAnimation].UpdateAnimation(aDeltaTime);
}
void AnimationHandler::AddAnimation(Animation* anAnimation)
{
	myAnimations[anAnimation->GetName()] = *anAnimation;
}

void AnimationHandler::ChangeAnimation(const std::string& anAnimation)
{
	DL_ASSERT(myAnimations.find(anAnimation) != myAnimations.end(), "Animation does not exist: ");
	if (myActiveAnimation != anAnimation)
	{
		if (myActiveAnimation != "")
		{
			if (myAnimations[myActiveAnimation].GetIsRunning() == false || myAnimations[myActiveAnimation].GetIsInteruptable() == true)
			{
				myAnimations[myActiveAnimation].StopAnimation();
				if (myAnimations[myActiveAnimation].GetInTransition() != "")
				{
					myAnimations[myAnimations[myActiveAnimation].GetInTransition()].SetHasPlayed(false);
				}
				if (myAnimations[myActiveAnimation].GetOutTransition() != "")
				{
					myAnimations[myAnimations[myActiveAnimation].GetOutTransition()].SetHasPlayed(false);
				}

				if (myAnimations[myActiveAnimation].GetOutTransition() == "" ||
					myAnimations[myAnimations[myActiveAnimation].GetOutTransition()].GetHasPlayed() == true)
				{
					if (myAnimations[anAnimation].GetInTransition() == "" ||
						myAnimations[myAnimations[anAnimation].GetInTransition()].GetHasPlayed() == true)
					{
						myActiveAnimation = anAnimation;
					}
					else if (myActiveAnimation != myAnimations[anAnimation].GetInTransition())
					{
						myActiveAnimation = myAnimations[anAnimation].GetInTransition();
						myAnimations[myActiveAnimation].StopAnimationAtEnd();
					}
				}
				else if (myActiveAnimation != myAnimations[anAnimation].GetOutTransition())
				{
					myActiveAnimation = myAnimations[myActiveAnimation].GetOutTransition();
					myAnimations[myActiveAnimation].StopAnimationAtEnd();
				}
				myAnimations[myActiveAnimation].StartAnimation();
			}
			else
			{
				myAnimations[myActiveAnimation].StopAnimationAtEnd();
			}
		}
		else
		{
			myActiveAnimation = anAnimation;
			myAnimations[myActiveAnimation].StartAnimation();
		}
	}
}