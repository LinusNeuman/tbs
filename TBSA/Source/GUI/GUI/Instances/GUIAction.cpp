#include "GUIAction.h"
#include <Message/PlayerIDMessage.h>
#include <PostMaster/SingletonPostMaster.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>
#include <CU/Utility/CommonCasts.h>
#include <Message/CurrentPlayerAP.h>

GUIAction::GUIAction() :
	myLocked(nullptr),
	myUnlockedGlow(nullptr),
	myIsLocked(false),
	myCanDo(false)
{
	SingletonPostMaster::AddReciever(RecieverTypes::eCurrentPlayerAP, *this);
}

GUIAction::~GUIAction()
{
	SingletonPostMaster::RemoveReciever(*this);

	SAFE_DELETE(myLocked);
	SAFE_DELETE(myUnlockedGlow);
}

void GUIAction::ResetAnimateGlow()
{
	myAnimateGlowState = GUIAnimateState::eFadingUp;
	myAnimateGlowTimer = 0.f;
	CU::Vector4f color = myUnlockedGlow->GetColor();
	color.w = 0.7f;
	myUnlockedGlow->SetColor(color);
}

void GUIAction::Create(const std::string& aSpritePath, CU::Vector2f aPosition, int aCost1, int aCost2)
{
	GUIButton::Create("ActionElement", aSpritePath, { 0, 0 }, aPosition, { 109, 93 }, true, true, true, false, true);

	myCostP1 = aCost1;
	myCostP2 = aCost2;

	myLocked = new StaticSprite();
	myLocked->Init(aSpritePath + "/Locked.dds", false, { 0, 0, 109, 93 });
	myLocked->SetLayer(enumRenderLayer::eGUI);

	myUnlockedGlow = new StaticSprite();
	myUnlockedGlow->Init(aSpritePath + "/Unlocked.dds", false, { 0, 0, 109, 93 });
	myUnlockedGlow->SetLayer(enumRenderLayer::eGUI);

	ResetAnimateGlow();
}

void GUIAction::AnimateGlow(const CommonUtilities::Time aTime)
{
	myAnimateGlowState == GUIAnimateState::eFadingUp ? FadeUpGlow(aTime) : FadeDownGlow(aTime);
}

void GUIAction::FadeUpGlow(const CommonUtilities::Time aTime)
{
	CU::Vector4f color = myUnlockedGlow->GetColor();
	if (color.w < 1.1f)
	{
		color.w += 0.5f * aTime.GetSeconds();
		if (color.w  > 1)
		{
			myAnimateGlowTimer += 2.5f * aTime.GetSeconds();
			if (myAnimateGlowTimer >= 1.0f)
			{
				myAnimateGlowState = GUIAnimateState::eFadingDown;
				myAnimateGlowTimer = 0.f;
			}
			color.w = 1;
		}
		myUnlockedGlow->SetColor(color);
	}
}

void GUIAction::FadeDownGlow(const CommonUtilities::Time aTime)
{
	CU::Vector4f color = myUnlockedGlow->GetColor();
	if (color.w >= 0.0f)
	{
		color.w -= 1.2f * aTime.GetSeconds();
		if (color.w < 0)
		{
			myAnimateGlowTimer += 2.5f * aTime.GetSeconds();
			if (myAnimateGlowTimer >= 1.0f)
			{
				myAnimateGlowState = GUIAnimateState::eFadingUp;
				myAnimateGlowTimer = 0.f;
			}
			color.w = 0;
		}
		myUnlockedGlow->SetColor(color);
	}
}

void GUIAction::Update(const CU::Time& aDelta)
{
	if (myCanDo == true)
	{
		GUIButton::Update(aDelta);

		if (myIsLocked == false)
		{
			AnimateGlow(aDelta);
		}
	}
}

void GUIAction::WhenClicked()
{
	// do stuff

	if (myCanDo == true)
	{
		GUIButton::WhenClicked();
	}
}

void GUIAction::WhenHovered()
{
	if (myCanDo == true)
	{
		GUIButton::WhenHovered();
	}
}

void GUIAction::Render()
{
	if (myCanDo == true)
	{
		if (myIsLocked == false)
		{
			GUIButton::Render();

			myUnlockedGlow->Draw(myPosition);
		}
		else
		{
			myLocked->Draw(myPosition);
		}
	}
	else
	{
		myLocked->Draw(myPosition);
	}
}

bool GUIAction::RecieveMessage(const CurrentPlayerAP& aMessage)
{
	if (aMessage.myType == RecieverTypes::eCurrentPlayerAP)
	{
		myPlayerAP = aMessage.myCurrentPlayerAP;
		if (aMessage.myCurrentPlayerID == 0)
		{
			if (myPlayerAP < myCostP1)
			{
				myIsLocked = true;
			}
			else
			{
				myIsLocked = false;
			}
		}
		else
		{
			if (myPlayerAP < myCostP2)
			{
				myIsLocked = true;
			}
			else
			{
				myIsLocked = false;
			}
		}
	}

	return true;
}
