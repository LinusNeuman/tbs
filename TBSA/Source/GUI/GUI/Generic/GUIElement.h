#pragma once
#include "CU/NameSpaceAliases.h"

#include <CU/Timer/Time.h>

#include <string>
#include <CU/GrowingArray/GrowingArray.h>

#include "GUI/Messaging/GUIMessageHandler.h"
#include <CU/Vectors/Vector.h>

#include <PostMaster/MessageReceiver.h>

#include <Rend/StaticSprite.h>

typedef unsigned char uchar;

struct GUIMessage;

class GUIElement : public MessageReciever
{
public:
	GUIElement();
	virtual ~GUIElement();
	virtual void Destroy();

	virtual void __forceinline SetIsometric(bool aIsIsometric);
	virtual void __forceinline SetEnabled(bool aIsEnabled);
	virtual void __forceinline SetName(const char* aName);
	virtual void __forceinline SetSprite(const char* aFilePath);

	virtual void __forceinline SetOnClick(GUIMessage* aGUIMessage);
	virtual void __forceinline SetOnHover(GUIMessage* aGUIMessage);

	virtual void __forceinline OnHover();
	virtual void __forceinline OnClick();

	virtual void Update(CommonUtilities::Time &aDelta) = 0;

	virtual void Render(CU::Vector2f aParentSpace);
protected:
	GUIMessageHandler myMessageHandler;

	StaticSprite* myBackground;
	StaticSprite* mySprite;
	CU::Vector2f myPosition;

	std::string myName;

	bool myIsEnabled;
	bool myIsIsometric;

	CU::GrowingArray<GUIElement*, unsigned char> myGUIChilds;
};

#include "GUIElement.inl"