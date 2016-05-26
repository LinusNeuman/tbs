#pragma once
#include "Animation.h"
#include <string>
#include "../Rend/StaticSprite.h"
#include "../../CommonUtilities/CU/Timer/TimeManager.h"

class Actor;

class AnimationHandler
{
public:
	AnimationHandler();
	~AnimationHandler();
	void Init(Actor* aHolder, std::map<std::string, Animation*> someAnimations);
	void Update();
	void ChangeAnimation(const std::string& anAnimation);
	void AddAnimation(Animation* anAnimation);
	inline StaticSprite* GetSprite();
	inline bool GetIsActive();
private:
	Actor* myHolder;
	std::string myActiveAnimation;
	std::map<std::string, Animation*> myAnimations;
};

inline StaticSprite* AnimationHandler::GetSprite()
{
	return myAnimations[myActiveAnimation]->GetSprite();
}

inline bool AnimationHandler::GetIsActive()
{
	if (myActiveAnimation != "")
	{
		return true;
	}
	return false;
}