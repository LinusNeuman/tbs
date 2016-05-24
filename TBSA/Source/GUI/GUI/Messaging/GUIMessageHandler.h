#pragma once
#include "Generic/GUIMessage.h"
#include <CU/StaticArray/StaticArray.h>

enum class eGUIMessageEvents
{
	eOnClick,
	eOnHover,
	eOnOpen,
	eOnClose,
	eOnAlternativeChosen,
};

class GUIMessageHandler
{
public:
	GUIMessageHandler();
	~GUIMessageHandler();

	void __forceinline SetOnClick(GUIMessage& aGUIMessage);
	void __forceinline SetOnHover(GUIMessage& aGUIMessage);

	void __forceinline Execute(eGUIMessageEvents aGUIMessageEvent);
private:
	CommonUtilities::StaticArray<GUIMessage*, 5> myMessageEvents;
};