#include "GUIElement.h"
#include <CU/Macros/Macros.h>
#include <PostMaster/SingletonPostMaster.h>


GUIElement::GUIElement()
{
	mySprite = nullptr;
	myGUIChilds.Init(1);
}


GUIElement::~GUIElement()
{
}

void GUIElement::Destroy()
{
	SingletonPostMaster::RemoveReciever(*this);

	SAFE_DELETE(mySprite);

	for (uchar u = 0; u < myGUIChilds.Size(); ++u)
	{
		myGUIChilds[u]->Destroy();
	}
}

void GUIElement::Init(const char* aName, const char* aSpritePath, bool aIsEnabled)
{
	myName = aName;
	mySprite->Init(aSpritePath);

	myIsEnabled = aIsEnabled;
}

void GUIElement::SetOnClick(GUIMessage& aGUIMessage)
{
	myMessageHandler.SetOnClick(aGUIMessage);
}

void GUIElement::SetOnHover(class GUIMessage& aGUIMessage)
{
	myMessageHandler.SetOnHover(aGUIMessage);
}

void GUIElement::OnHover()
{
	myMessageHandler.Execute(eGUIMessageEvents::eOnHover);
}

void GUIElement::OnClick()
{
	myMessageHandler.Execute(eGUIMessageEvents::eOnClick);
}

void GUIElement::Render(CU::Vector2f aParentSpace)
{
	mySprite->Draw(aParentSpace + myPosition);

	for (uchar u = 0; u < myGUIChilds.Size(); ++u)
	{
		myGUIChilds[u]->Render(myPosition);
	}
}
