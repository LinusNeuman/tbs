#include "GUIFactory.h"
#include <iostream>

GUIFactory* GUIFactory::myInstance = nullptr;

GUIFactory::GUIFactory()
{
}


GUIFactory::~GUIFactory()
{
}

void GUIFactory::Load()
{

}

CU::GrowingArray<GUIElement*, uchar>& GUIFactory::GetLoadedGUI(const char* aStateName)
{
	if (myGUILookup.find(aStateName) == myGUILookup.end())
	{
		DL_PRINT(std::string("GUI State was not found in lookup: " + std::string(aStateName)).c_str());
		std::cout << "GUI State was not found in lookup: " << aStateName << std::endl;
	}
	else
	{
		uchar begin = myGUILookup[aStateName].myBegin;
		uchar end = myGUILookup[aStateName].myEnd;

		CU::GrowingArray<GUIElement*, uchar> returnArray;
		returnArray.Init(end - begin);

		for (uchar ch = begin; ch < end; ++ch)
		{
			returnArray.Add(myGUIElements[ch]);
		}

		return returnArray;
	}
}
