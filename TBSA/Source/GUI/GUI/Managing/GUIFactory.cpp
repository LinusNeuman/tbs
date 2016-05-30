#include "GUIFactory.h"
#include <iostream>

#include <CU/Timer/Timer.h>
#include <CU/Timer/TimeManager.h>

#include "../JSONWrapper/JsonWrapper/JsonWrapper.h"
#include <GUI/Instances/GUIButton.h>

GUIFactory* GUIFactory::myInstance = nullptr;

GUIFactory::GUIFactory()
{
}


GUIFactory::~GUIFactory()
{
	//myGUIElements.DeleteAll();
}

void GUIFactory::Load()
{
	myGUIElements.Init(1);

	std::cout << "Started loading all GUI.." << std::endl;
	CU::Timer loadTimer;

	// json wrapper load all gui files

	// one master file that tells which states we have
	// then load them and put them into the map with growingarrays

	GUIButton* newButton = new GUIButton();

	// everything will be read from json later
	newButton->Create(
		"ExitButton",
		"Sprites/GUI/InGame/ExitButton/",
		{ 1920.f, 1080.f },
		{ -(41.f + 223.f), -(37.f + 117.f) },
		{ 223, 117 }
	);
	newButton->SetAction(new GUIMessage(RecieverTypes::eEndTurn), eGUIMessageEvents::eOnClick);

	myGUIElements.Add(newButton);
	myGUILookup["InGame"].myBegin = 0;
	myGUILookup["InGame"].myEnd = 0;

	GUIButton* quitButton = new GUIButton();

	quitButton->Create(
		"QuitButton",
		"Sprites/GUI/MainMenu/QuitButton/",
		{ 0.f, 0.f }, { 1920.f / 2.f, 1080.f / 2.f + 250 }, { 200, 100 });

	quitButton->SetAction(new GUIMessage(RecieverTypes::eExitGame), eGUIMessageEvents::eOnClick);
	myGUIElements.Add(quitButton);

	GUIButton* playButton = new GUIButton();

	playButton->Create(
		"PlayButton",
		"Sprites/GUI/MainMenu/PlayButton/",
		{ 0.f, 0.f }, { 1920.f / 2.f, 1080.f / 2.f }, { 200, 100 });

	playButton->SetAction(new GUIMessage(RecieverTypes::eStartUpLevel), eGUIMessageEvents::eOnClick);
	myGUIElements.Add(playButton);

	myGUILookup["MainMenu"].myBegin = 1;
	myGUILookup["MainMenu"].myEnd = 2;

	CU::TimeManager::Update();

	std::cout << "Loading all GUI took " << loadTimer.GetTime().GetMilliSeconds() << " ms" << std::endl;
}

CU::GrowingArray<GUIElement*, uchar>* GUIFactory::GetLoadedGUI(const char* aStateName)
{
	if (myGUILookup.find(aStateName) == myGUILookup.end())
	{
		DL_PRINT(std::string("GUI State was not found in lookup: " + std::string(aStateName)).c_str());
	}
	else
	{
		uchar begin = myGUILookup[aStateName].myBegin;
		uchar end = myGUILookup[aStateName].myEnd;
		uchar range = end - begin;
		++range;

		CU::GrowingArray<GUIElement*, uchar>* returnArray = new CU::GrowingArray<GUIElement*, uchar>(range);

		for (uchar ch = begin; ch < begin + range; ++ch)
		{
			returnArray->Add(myGUIElements[ch]);
		}

		return returnArray;
	}

	return nullptr;
}