#pragma once
#include "CU/NameSpaceAliases.h"

#include <CU/Timer/Time.h>

#include <string>
#include <CU/GrowingArray/GrowingArray.h>

#include "GUI/Messaging/GUIMessageHandler.h"
#include <CU/Vectors/Vector.h>

#include <PostMaster/MessageReceiver.h>

#include <Rend/StaticSprite.h>
#include <CU/Intersection/Shapes2D/AABB2D.h>
#include <CU/Intersection/Intersection2D.h>
#include <Input/SingletonIsometricInputWrapper.h>

typedef unsigned char uchar;

struct GUIMessage;

class GUIElement : public MessageReciever
{
public:
	GUIElement();
	virtual ~GUIElement();
	virtual void Destroy();

	virtual void __forceinline Create(const char* aName, const char* aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2i aWhiteSpaceInPixels, bool aIsIsometric = false, bool aIsEnabled = true);

	virtual void __forceinline SetAction(GUIMessage* aGUIMessage, eGUIMessageEvents aMessageEvent);

	virtual bool __forceinline OnAction(eGUIMessageEvents aMessageEvent, CU::Vector2f aMousePosition);

	virtual void Update(CommonUtilities::Time &aDelta) = 0;

	virtual void Render();
protected:
	GUIMessageHandler myMessageHandler;

	StaticSprite* myBackground;
	StaticSprite* mySprite;

	CU::Vector2f myPosition;
	CU::Vector2f myParentSpace;
	CU::Vector2f mySize;

	Intersection2D::AABB2D myCollisionBox;

	std::string myName;

	bool myIsEnabled;
	bool myIsIsometric;

	CU::GrowingArray<GUIElement*, unsigned char> myGUIChilds;
};

#include "GUIElement.inl"