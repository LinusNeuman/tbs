#include "GUIPortraitPassive.h"
#include <Message/PlayerIDMessage.h>
#include <PostMaster/SingletonPostMaster.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>
#include <CU/Utility/CommonCasts.h>

GUIPortraitPassive::GUIPortraitPassive() :
	myCharacter0(nullptr),
	myCharacter1(nullptr)
{
	SingletonPostMaster::AddReciever(RecieverTypes::eClickedOnPlayer, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eChangeSelectedPlayer, *this);
}

GUIPortraitPassive::~GUIPortraitPassive()
{
	SingletonPostMaster::RemoveReciever(*this);

	SAFE_DELETE(myCharacter0);
	SAFE_DELETE(myCharacter1);
}

void GUIPortraitPassive::Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aAnimated, bool aPlayClickSound, bool aPlayHoverSound, bool aIsIsometric, bool aIsEnabled)
{
	myName = aName;
	myIsIsometric = aIsIsometric;
	myIsAnimated = aAnimated;

	myCharacter0 = new StaticSprite();
	myCharacter0->Init(
		aSpritePath + "/Ginger.dds",
		myIsIsometric,
		{
			0.f, 0.f,
			aImageSize.x,
			aImageSize.y
		}
	);
	myCharacter0->SetLayer(enumRenderLayer::eGUI);

	myCharacter1 = new StaticSprite();
	myCharacter1->Init(
		aSpritePath + "/LongJohn.dds",
		myIsIsometric,
		{
			0.f, 0.f,
			aImageSize.x,
			aImageSize.y
		}
	);
	myCharacter1->SetLayer(enumRenderLayer::eGUI);

	mySpriteHovered = new StaticSprite();
	mySpriteHovered->Init(
		aSpritePath + "/Hover.dds",
		myIsIsometric,
		{
			0.f, 0.f,
			aImageSize.x,
			aImageSize.y
		}
	);
	mySpriteHovered->SetLayer(enumRenderLayer::eGUI);

	

	myParentSpace = aParentSpace;
	myPosition = aParentSpace + anOffset;

	myIsEnabled = aIsEnabled;

	CU::Vector2f boxPosition = myPosition;

	boxPosition.x /= FLOATCAST(SingletonDataHolder::GetTargetResolution().x);
	boxPosition.y /= FLOATCAST(SingletonDataHolder::GetTargetResolution().y);

	CU::Vector2f penisapa = myCharacter0->GetSizeInPixels();

	myCollisionBox.SetWithMaxAndMinPos(
	boxPosition,
	{
		boxPosition.x + myCharacter0->GetSizeInPixels().x / 1920.f/*SingletonDataHolder::GetTargetResolution().x*/,
		boxPosition.y + myCharacter0->GetSizeInPixels().y / 1080/*SingletonDataHolder::GetTargetResolution().y*/
	});

	mySprite = mySpriteUnpressed;

	if (aPlayHoverSound == true)
	{
		myHoverSound = new SoundEffect();
		myHoverSound->Init("Sounds/GUI/HoverMenuItem.ogg");
	}

	if (aPlayClickSound == true)
	{
		myClickSound = new SoundEffect();
		myClickSound->Init("Sounds/GUI/HoverMenuItem2.ogg");
	}

	ResetAnimate();
}

void GUIPortraitPassive::Update(const CU::Time& aDelta)
{
	if (myIsCurrentlyHovered == true)
	{
		Animate(aDelta);
	}
	mySprite = mySpriteUnpressed;
}

void GUIPortraitPassive::WhenClicked()
{

}

void GUIPortraitPassive::WhenHovered()
{
	GUIButton::WhenHovered();
}

void GUIPortraitPassive::Render()
{
	if (myCharacter0 == nullptr || myCharacter1 == nullptr)
	{
		return;
	}

	if (myPlayerID == 1)
	{
		myCharacter0->Draw(myPosition);
	}
	else
	{
		myCharacter1->Draw(myPosition);
	}

	if (myIsAnimated == true)
	{
		if (myIsCurrentlyHovered == true)
		{
			mySpriteHovered->Draw(myPosition);
		}
	}
}

bool GUIPortraitPassive::RecieveMessage(const PlayerIDMessage& aMessage)
{
	myPlayerID = aMessage.myPlayerID;
	return true;
}

bool GUIPortraitPassive::RecieveMessage(const GUIMessage & aMessage)
{
	if (aMessage.myType == RecieverTypes::eChangeSelectedPlayer || aMessage.myType == RecieverTypes::eClickedOnPlayer)
	{
		const PlayerIDMessage * tempmessageerer = dynamic_cast<const PlayerIDMessage*>(&aMessage);
		RecieveMessage(*tempmessageerer);
	}
	return true;
}