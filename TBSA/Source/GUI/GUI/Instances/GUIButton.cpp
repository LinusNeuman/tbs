#include "GUIButton.h"


GUIButton::GUIButton()
{
	mySpriteHovered = nullptr;
	mySpritePressed = nullptr;
	mySpriteUnpressed = nullptr;
}


GUIButton::~GUIButton()
{
}

void GUIButton::Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aIsIsometric, bool aIsEnabled)
{
	myName = aName;
	myIsIsometric = aIsIsometric;

	mySpritePressed = new StaticSprite();
	mySpritePressed->Init(
		aSpritePath + "Pressed.dds",
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
		aSpritePath + "Unpressed.dds",
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
		aSpritePath + "Hover.dds",
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
		(myPosition.x / 1920.f) + mySpriteUnpressed->GetSize().x,
		(myPosition.y / 1080.f) + mySpriteUnpressed->GetSize().y
	});

	mySprite = mySpriteUnpressed;
}

void GUIButton::Update(const CU::Time& aDelta)
{
	if (myIsCurrentlyHovered == true)
	{
		mySprite = mySpriteHovered;
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

	// Change image to hovered image. 
	// In the future, this needs to have in mind that if the button is pressed, and
}
