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
			mySprite = mySpriteHovered;
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
