#pragma once
#include <GUI/Messaging/Generic/GUIMessage.h>
#include <CU/StaticArray/StaticArray.h>
#include <PostMaster/SingletonPostMaster.h>

enum class eGUIMessageEvents
{
	eOnClick,
	eOnHover,
	eOnDrag,
	eOnOpen,
	eOnClose,
	eOnAlternativeChosen,
	eEnumLength,
};

class GUIMessageHandler
{
public:
	GUIMessageHandler();
	~GUIMessageHandler();

	void __forceinline SetOnClick(GUIMessage* aGUIMessage);
	void __forceinline SetOnHover(GUIMessage* aGUIMessage);

	void __forceinline Execute(eGUIMessageEvents aGUIMessageEvent);
private:
	CommonUtilities::StaticArray<GUIMessage*, static_cast<int>(eGUIMessageEvents::eEnumLength)> myMessageEvents;
};

#include <GUI/Messaging/GUIMessageHandler.inl>