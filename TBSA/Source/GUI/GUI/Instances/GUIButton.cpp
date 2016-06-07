#include "GUIButton.h"

GUIButton::GUIButton() : 
	mySpritePressed(nullptr), 
	mySpriteHovered(nullptr),
	mySpriteUnpressed(nullptr),
	myHoverSound(nullptr),
	myClickSound(nullptr)
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

void GUIButton::Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aAnimated, bool aPlayClickSound, bool aPlayHoverSound, bool aIsIsometric, bool aIsEnabled)
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

	myCollisionBox.SetWithMaxAndMinPos(
	{ myPosition.x / 1920.f, myPosition.y / 1080.f },
	{
		(myPosition.x / 1920.f) + mySpriteUnpressed->GetSizeWithoutWhiteSpace().x / 1920.f,
		(myPosition.y / 1080.f) + mySpriteUnpressed->GetSizeWithoutWhiteSpace().y / 1080.f
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
	
	myAnimateTimer = 0.f;
	myAnimateState = GUIAnimateState::eFadingDown;
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
			myAnimateTimer += 0.5f * aTime.GetSeconds();
			if (myAnimateTimer >= 1.0f)
			{
				myAnimateState = GUIAnimateState::eFadingDown;
			}
			color.w = 1;
		}
		mySpriteHovered->SetColor(color);
	}
}

void GUIButton::FadeDown(const CommonUtilities::Time aTime)
{
	CU::Vector4f color = mySpriteHovered->GetColor();
	if (color.w > 0.0f)
	{
		color.w -= 1.0f * aTime.GetSeconds();
		if (color.w < 0)
		{
			myAnimateState = GUIAnimateState::eFadingUp;
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
	}
}

void GUIButton::WhenClicked()
{
	if (myClickSound != nullptr)
	{
		myClickSound->Play(1.0f);
	}
}
