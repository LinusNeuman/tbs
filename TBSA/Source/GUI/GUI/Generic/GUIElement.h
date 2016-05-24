#pragma once
#include "CU/NameSpaceAliases.h"

#include <CU/Timer/Time.h>

#include <string>
#include <CU/GrowingArray/GrowingArray.h>

#include "../Messaging/GUIMessageHandler.h"
#include <CU/Vectors/Vector.h>

//#include <PostMaster/MessageReceiver.h>
#include "PostMaster/MessageReceiver.h"
#include <Rend/StaticSprite.h>

typedef unsigned char uchar;

class GUIMessage;

class GUIElement : public MessageReciever
{
public:
	GUIElement();
	virtual ~GUIElement();
	virtual void Destroy();

	virtual void Init(const char* aName, const char* aSpritePath, bool aIsEnabled);

	virtual void __forceinline SetOnClick(GUIMessage& aGUIMessage);
	virtual void __forceinline SetOnHover(GUIMessage& aGUIMessage);

	virtual void OnHover();
	virtual void OnClick();

	virtual void Update(CommonUtilities::Time &aDelta) = 0;

	virtual void Render(CU::Vector2f aParentSpace);
protected:
	GUIMessageHandler myMessageHandler;

	StaticSprite* mySprite;
	CU::Vector2f myPosition;

	std::string myName;

	bool myIsEnabled;

	CU::GrowingArray<GUIElement*, unsigned char> myGUIChilds;
};

