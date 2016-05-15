#include "GUIFactory.h"
#include <iostream>

#include <CU/Timer/Timer.h>

#include "../JSONWrapper/JsonWrapper/JsonWrapper.h"

GUIFactory* GUIFactory::myInstance = nullptr;

GUIFactory::GUIFactory()
{
}


GUIFactory::~GUIFactory()
{
}

void GUIFactory::Load()
{
	std::cout << "Started loading all GUI.." << std::endl;
	CU::Timer loadTimer;

	// json wrapper load all gui files

	// one master file that tells which states we have
	// then load them and put them into the map with growingarrays


	
	std::cout << "Loading all GUI took " << loadTimer.GetTime().GetMilliSeconds() << " ms" << std::endl;
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
