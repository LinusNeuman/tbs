#include "GUIElement.h"
#include <CU/Macros/Macros.h>
#include <PostMaster/SingletonPostMaster.h>
#include <Rend/StaticSprite.h>

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

void GUIElement::Render()
{
	if (mySprite != nullptr)
	{
		mySprite->Draw(myParentSpace + myPosition);
	}

	for (uchar u = 0; u < myGUIChilds.Size(); ++u)
	{
		myGUIChilds[u]->Render();
	}
}
