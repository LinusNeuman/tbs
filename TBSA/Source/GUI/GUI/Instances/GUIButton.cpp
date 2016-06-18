#include "GUIButton.h"
#include <CU/Utility/DataHolder/SingletonDataHolder.h>
#include <CU/Utility/CommonCasts.h>
#include "CU/Utility/GameSpecificTypeDefs.h"

//#define EditorScreenSizeX 19-20.f
//#define EditorScreenSizeY 10-80.f

GUIButton::GUIButton() : 
	mySpritePressed(nullptr), 
	mySpriteHovered(nullptr),
	mySpriteUnpressed(nullptr),
	myHoverSound(nullptr),
	myClickSound(nullptr),
	myFulHax(false)
{
}


GUIButton::~GUIButton()
{
	SAFE_DELETE(myHoverSound);
	SAFE_DELETE(myClickSound);
	SAFE_DELETE(mySpriteUnpressed);
	SAFE_DELETE(mySpritePressed);
	SAFE_DELETE(mySpriteHovered);
}

void GUIButton::Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aAnimated, bool aPlayClickSound, bool aPlayHoverSound, const char* aTooltip, CU::Vector2i aTooltipsize, float aTextOffset, bool aIsIsometric, bool aIsEnabled, float aPriority)
{
	myName = aName;
	myIsIsometric = aIsIsometric;
	myIsAnimated = aAnimated;

	mySpritePressed = new StaticSprite();
	mySpritePressed->Init(
		aSpritePath + "/Pressed.dds",
		myIsIsometric,
		{
			0.f, 0.f,
			aImageSize.x,
			aImageSize.y
		}
	);
	mySpritePressed->SetLayer(enumRenderLayer::eGUI);

	mySpritePressed->SetRenderPriority(aPriority);

	mySpriteUnpressed = new StaticSprite();
	mySpriteUnpressed->Init(
		aSpritePath + "/Unpressed.dds",
		myIsIsometric,
		{
			0.f, 0.f,
			aImageSize.x,
			aImageSize.y
		}
	);
	mySpriteUnpressed->SetLayer(enumRenderLayer::eGUI);
	mySpriteUnpressed->SetRenderPriority(aPriority);

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
	mySpriteHovered->SetRenderPriority(aPriority);

	myParentSpace = aParentSpace;
	myPosition = aParentSpace + anOffset;
	myIsEnabled = aIsEnabled;

	float renderScale = FLOATCAST(SingletonDataHolder::GetTargetResolution().y) / (1080.f);

	CU::Vector2f boxPosition = { myPosition.x / SingletonDataHolder::GetTargetResolutionf().x, myPosition.y / SingletonDataHolder::GetTargetResolutionf().y };
	CU::Vector2f spriteSizeNorm = { FLOATCAST(mySpriteUnpressed->GetSizeInPixels().x) / (1920.f), FLOATCAST(mySpriteUnpressed->GetSizeInPixels().y) / (1080.f) };

	myCollisionBox.SetWithMaxAndMinPos(
		boxPosition,
		{
			boxPosition.x + spriteSizeNorm.x,
			boxPosition.y + spriteSizeNorm.y
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

	myTooltip.Init(aTooltip, aTooltipsize, 1.f, aTextOffset);
}

void GUIButton::ResetAnimate()
{
	myAnimateState = GUIAnimateState::eFadingUp;
	myAnimateTimer = 0.f;
	CU::Vector4f color = mySpriteHovered->GetColor();
	color.w = 0.7f;
	mySpriteHovered->SetColor(color);
}

void GUIButton::Animate(const CommonUtilities::Time aTime)
{
	myAnimateState == GUIAnimateState::eFadingUp ? FadeUp(aTime) : FadeDown(aTime);
}

void GUIButton::FadeUp(const CommonUtilities::Time aTime)
{
	CU::Vector4f color = mySpriteHovered->GetColor();
	if (color.w < 1.1f)
	{
		color.w += 0.5f * aTime.GetSeconds();
		if (color.w  > 1)
		{
			myAnimateTimer += 2.5f * aTime.GetSeconds();
			if (myAnimateTimer >= 1.0f)
			{
				myAnimateState = GUIAnimateState::eFadingDown;
				myAnimateTimer = 0.f;
			}
			color.w = 1;
		}
		mySpriteHovered->SetColor(color);
	}
}

void GUIButton::FadeDown(const CommonUtilities::Time aTime)
{
	CU::Vector4f color = mySpriteHovered->GetColor();
	if (color.w >= 0.0f)
	{
		color.w -= 1.2f * aTime.GetSeconds();
		if (color.w < 0)
		{
			myAnimateTimer += 2.5f * aTime.GetSeconds();
			if (myAnimateTimer >= 1.0f)
			{
				myAnimateState = GUIAnimateState::eFadingUp;
				myAnimateTimer = 0.f;
			}
			color.w = 0;
		}
		mySpriteHovered->SetColor(color);
	}
}

void GUIButton::Update(const CU::Time& aDelta)
{
	if (myIsCurrentlyHovered == true)
	{
		if (myIsCurrentlyPressed == true)
		{
			mySprite = mySpritePressed;
		}
		else
		{
			if (myIsAnimated == true)
			{
				Animate(aDelta);
				mySprite = mySpriteUnpressed;
			}
			else
			{
				mySprite = mySpriteHovered;
			}
		}
	}
	else if (myIsCurrentlyPressed == true)
	{
		mySprite = mySpritePressed;
	}
	else
	{
		mySprite = mySpriteUnpressed;
	}

	if (myFulHax == false)
	{
		myTooltip.Update(aDelta);
	}
}

void GUIButton::Render()
{
	if (mySprite != nullptr)
	{
		mySprite->Draw(myPosition);
		if (myIsAnimated == true)
		{
			if (myIsCurrentlyHovered == true && myIsCurrentlyPressed == false)
			{
				mySpriteHovered->Draw(myPosition);
			}
		}
	}

	if (myFulHax == false)
	{
		myTooltip.Render();
	}
}

void GUIButton::WhenHovered()
{
	// Was not previously hovered. 
	// Do things that we only want this button to do once, such as play sound.

	if (myIsCurrentlyHovered == false)
	{
		if (myHoverSound != nullptr)
		{
			myHoverSound->Play(1.0f);
		}

		myTooltip.Show();
	}
}

void GUIButton::WhenClicked()
{
	if (myClickSound != nullptr)
	{
		myClickSound->Play(1.0f);
	}
}

void GUIButton::WhenLeaved()
{
	ResetAnimate();

	myTooltip.Close();
}
