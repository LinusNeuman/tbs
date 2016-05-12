#pragma once
#include "GUIMessage.h"
#include "../../../CommonUtilities/CU/StaticArray/StaticArray.h"

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
private:
	CommonUtilities::StaticArray<GUIMessage, 5> myMessageEvents;
};

