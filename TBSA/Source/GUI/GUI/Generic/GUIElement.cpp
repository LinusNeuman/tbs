#include "GUIElement.h"
#include <CU/Macros/Macros.h>
#include <PostMaster/SingletonPostMaster.h>
#include <Rend/StaticSprite.h>

GUIElement::GUIElement()
{
	mySpriteUnpressed = nullptr;
	mySpritePressed = nullptr;
	mySpriteHovered = nullptr;
	myGUIChilds.Init(1);
}


GUIElement::~GUIElement()
{
}

void GUIElement::Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aIsIsometric, bool aIsEnabled)
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
}

void GUIElement::Destroy()
{
	SingletonPostMaster::RemoveReciever(*this);

	//SAFE_DELETE(mySprite);

	for (uchar u = 0; u < myGUIChilds.Size(); ++u)
	{
		myGUIChilds[u]->Destroy();
	}
}

void GUIElement::Render()
{
	if (mySpriteUnpressed != nullptr)
	{
		mySpriteUnpressed->Draw(myPosition);
	}

	for (uchar u = 0; u < myGUIChilds.Size(); ++u)
	{
		myGUIChilds[u]->Render();
	}
}
