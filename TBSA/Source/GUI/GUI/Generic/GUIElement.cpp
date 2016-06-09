#include "GUIElement.h"
#include <CU/Macros/Macros.h>
#include <PostMaster/SingletonPostMaster.h>
#include <Rend/StaticSprite.h>
#include "Message\LogTextMessage.h"

GUIElement::GUIElement()
{
	mySprite = nullptr;

	myIsCurrentlyHovered = false;
	myIsCurrentlyPressed = false;

	//myGUIChilds.Init(1);
}


GUIElement::~GUIElement()
{
}

void GUIElement::Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aIsIsometric, bool aIsEnabled)
{
}

void GUIElement::Destroy()
{
	SingletonPostMaster::RemoveReciever(*this);

	//SAFE_DELETE(mySprite);

	/*for (uchar u = 0; u < myGUIChilds.Size(); ++u)
	{
		myGUIChilds[u]->Destroy();
	}*/
}

void GUIElement::WhenHovered()
{
}

void GUIElement::WhenClicked()
{
}

void GUIElement::WhenLeaved()
{

}

void GUIElement::Render()
{
	if (mySprite != nullptr)
	{
		mySprite->Draw(myPosition);
	}

	/*for (uchar u = 0; u < myGUIChilds.Size(); ++u)
	{
		myGUIChilds[u]->Render();
	}*/
}
