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
	
	virtual void Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aIsIsometric = false, bool aIsEnabled = true);

	virtual void Destroy();

	void __forceinline SetAction(GUIMessage* aGUIMessage, eGUIMessageEvents aMessageEvent);

	
	bool __forceinline OnAction(eGUIMessageEvents aMessageEvent, CU::Vector2f aMousePosition);

	virtual void WhenHovered();
	virtual void WhenClicked();

	bool __forceinline GetIsHovered();

	virtual void Update(const CU::Time &aDelta) = 0;

	virtual void Render();
protected:
	GUIMessageHandler myMessageHandler;

	StaticSprite* mySprite;

	CU::Vector2f myPosition;
	CU::Vector2f myParentSpace;

	Intersection2D::AABB2D myCollisionBox;

	std::string myName;

	bool myIsEnabled;
	bool myIsIsometric;

	bool myIsCurrentlyHovered;
	bool myIsCurrentlyPressed;

	//CU::GrowingArray<GUIElement*, unsigned char> myGUIChilds;
};

#include "GUIElement.inl"