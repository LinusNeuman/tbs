#include "stdafx.h"
#include "SplashState.h"
#include <CU/InputWrapper/SingletonInputWrapper.h>
#include "MenuState.h"
#include <StateStack/ProxyStateStack.h>


Splash::Splash()
{

}

Splash::Splash(const char* aPath)
{
	mySprite = new StaticSprite();
	mySprite->Init(aPath, false, CU::Vector4f::Zero, {0.5f,0.5f});
	mySprite->SetColor({ 1, 1, 1, 0 });

	myFadeState = eSplashFadeState::eFadingUp;

	myIsDone = false;
	myStayTimer = 0.f;
}

Splash::~Splash()
{
	SAFE_DELETE(mySprite);
}

bool Splash::Update(const CU::Time& aDeltaTime)
{
	return Fade(aDeltaTime);
}

void Splash::Render()
{
	/*mySprite->Draw(
	{ 
		(1920.f * 0.5f) - ((mySprite->GetSize().x * 1920.f)* 0.5f), 
		(1080.f * 0.5f) - ((mySprite->GetSize().y) * 1080.f)
	});*/

	mySprite->Draw({ 1920.f * 0.5f, 1080.f * 0.5f });
}

bool Splash::Fade(const CU::Time& aDelta)
{
	myFadeState == eSplashFadeState::eFadingUp ? FadeUp(aDelta) : FadeDown(aDelta);

	if (myFadeState == eSplashFadeState::eFadingUp)
	{
		FadeUp(aDelta);
	}
	else
	{
		FadeDown(aDelta);
	}

	return myIsDone;
}

void Splash::FadeUp(const CU::Time& aDelta)
{
	CU::Vector4f color = mySprite->GetColor();
	if (color.w < 1.1f)
	{
		color.w += 0.5f * aDelta.GetSeconds();
		if (color.w  > 1)
		{
			myStayTimer += 0.5f * aDelta.GetSeconds();
			if (myStayTimer >= 1.0f)
			{
				myFadeState = eSplashFadeState::eFadingDown;
			}
			color.w = 1;
		}
		mySprite->SetColor(color);
	}
}

void Splash::FadeDown(const CU::Time& aDelta)
{
	CU::Vector4f color = mySprite->GetColor();
	if (color.w > 0.0f)
	{
		color.w -= 1.0f * aDelta.GetSeconds();
		if (color.w < 0)
		{
			myIsDone = true;
			color.w = 0;
		}
		mySprite->SetColor(color);
	}
}


SplashState::SplashState()
{
	myCurrentSplash = 0;

	mySplashes[0] = new Splash("Sprites/Splash/TGA.dds");
	mySplashes[1] = new Splash("Sprites/Splash/Group.dds");

	myWaitTimer = 0.f;
}


SplashState::~SplashState()
{
	
}

void SplashState::Init()
{

}

eStackReturnValue SplashState::Update(const CU::Time& aTimeDelta, ProxyStateStack& aStateStack)
{
	static bool returnBool;

	//myWaitTimer += 0.2f * aTimeDelta.GetSeconds();
	//if (myWaitTimer >= 1.0f)
	//{
		if (myCurrentSplash < 2)
		{
			returnBool = mySplashes[myCurrentSplash]->Update(aTimeDelta);
		}

		if (IsometricInput::GetKeyPressed(DIK_RETURN) ||
			IsometricInput::GetKeyPressed(DIK_SPACE) ||
			IsometricInput::GetKeyPressed(DIK_ESCAPE))
		{
			if (myCurrentSplash < 1)
			{
				++myCurrentSplash;
			}
			else
			{
				MenuState* newState = new MenuState();
				newState->Init();
				aStateStack.AddMainState(newState);
			}
		}

		if (returnBool == true && myCurrentSplash >= 1)
		{
			MenuState* newState = new MenuState();
			newState->Init();
			aStateStack.AddMainState(newState);
		}
		else if (returnBool == true)
		{
			++myCurrentSplash;
		}

	//}


	return eStackReturnValue::eStay;
}

void SplashState::Draw() const
{
	if (myCurrentSplash < 2)
	{
		mySplashes[myCurrentSplash]->Render();
	}
}
