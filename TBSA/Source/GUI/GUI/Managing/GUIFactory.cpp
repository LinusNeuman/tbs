#include "GUIFactory.h"
#include <iostream>

#include <CU/Timer/Timer.h>
#include <CU/Timer/TimeManager.h>
#include <GUI/Instances/GUIButton.h>

GUIFactory* GUIFactory::myInstance = nullptr;

#define VIRTUALSCREENWIDTH 1920.f
#define VIRTUALSCREENHEIGHT 1080.f

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

	picojson::value rootValue = myJSON.LoadPicoValue("Data/GUI/root.json");
	picojson::array arrayJson = rootValue.get("GameStates").get<picojson::array>();//myJSON.GetPicoArray("GameStates", rootValue.get<picojson::object>());

	int elementsAdded = 0;
	
	for (size_t i = 0; i < arrayJson.size(); ++i)
	{
		const std::string currentStateName = myJSON.GetString("myName", arrayJson[i].get<picojson::object>());
		
		picojson::array arrayElements = myJSON.GetPicoArray("guiElements", arrayJson[i].get("myGUIData").get<picojson::object>());

		for (size_t j = 0; j < arrayElements.size(); ++j)
		{
			//if (arrayElements[j].contains("myPressed") == true)
			//{
			//	//hantera pressed
			//}

			//if (arrayElements[j].contains("myHover") == true)
			//{
			//	//hantera Hover
			//}

			const std::string name = myJSON.GetString("Name", arrayElements[j].get<picojson::object>());
			myGUILookup[currentStateName].myBegin = elementsAdded;


			//if (arrayElements[j].contains("$type") == true)
			//{
				//const std::string type = myJSON.GetString("$type", arrayElements[j].get<picojson::object>());

			/*	if (type == "GUIEditor.GUIButton, GUIEditor")
				{*/

					const std::string imagePath = myJSON.GetString("myImagesPath", arrayElements[j].get<picojson::object>());

					const CU::Vector2f position = myJSON.GetVector2f("myPositionX", "myPositionY", arrayElements[j].get<picojson::object>());

					const CU::Vector2f size = myJSON.GetVector2f("mySizeX", "mySizeY", arrayElements[j].get<picojson::object>());

					const bool shouldPlayClickSound = myJSON.GetBool("myShouldPlayClickSound", arrayElements[j].get<picojson::object>());

					const bool enabled = myJSON.GetBool("myIsEnabled", arrayElements[j].get<picojson::object>());

					const bool isometric = myJSON.GetBool("myIsIsometric", arrayElements[j].get<picojson::object>());

					picojson::object events = arrayElements[j].get("Events").get<picojson::object>();
					const std::string clickEvent = myJSON.GetString("Click", events);
					const std::string hoverEvent = myJSON.GetString("Hover", events);

					GUIButton* newButton = new GUIButton();
					newButton->Create(
						name.c_str(),
						imagePath,
						{ 0.f, 0.f },
						position,
						size,
						isometric,
						enabled
					);

					// also add tooltip 

					// also add events


					if (clickEvent == "Turn")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eTurn), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "ExitGame")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eExitGame), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "PlayGame")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::ePlayGame), eGUIMessageEvents::eOnClick);
					}

				/*}*/
			//}


					myGUIElements.Add(newButton);
					myGUILookup[currentStateName].myEnd = elementsAdded;

					++elementsAdded;
		}
	}

	// json wrapper load all gui files

	// one master file that tells which states we have
	// then load them and put them into the map with growingarrays

	//GUIButton* newButton = new GUIButton();

	//// everything will be read from json later
	//newButton->Create(
	//	"ExitButton",
	//	"Sprites/GUI/InGame/EndTurnButton/",
	//	{ 1920.f, 1080.f },
	//	{ -(41.f + 223.f), -(37.f + 117.f)},
	//	{ 223, 117}
	//);
	//newButton->SetAction(new GUIMessage(RecieverTypes::eTurn), eGUIMessageEvents::eOnClick);

	//myGUIElements.Add(newButton);


	//GUIButton* menuButton = new GUIButton();

	//menuButton->Create(
	//	"MenuButton",
	//	"Sprites/GUI/InGame/MenuButton/",
	//	{ 0, 0 },
	//	{ 26, 175 },
	//	{ 129, 69 }
	//);

	//GUIButton* portrait = new GUIButton();

	//portrait->Create(
	//	"NPCPortrait",
	//	"Sprites/GUI/InGame/PortraitNPC/",
	//	{ 0, 0 },
	//	{ 26, 29 },
	//	{ 130, 130 }
	//);

	//GUIButton* textbox = new GUIButton();

	//textbox->Create(
	//	"NPCTextBox",
	//	"Sprites/GUI/InGame/NPCTextBox/",
	//	{ 0, 0 },
	//	{ 165, 29 },
	//	{ 381, 214 }
	//);

	//GUIButton* playerPortrait = new GUIButton();

	//playerPortrait->Create(
	//	"PlayerPortrait",
	//	"Sprites/GUI/InGame/PlayerPortrait/",
	//	{ 0, 1080 },
	//	{ 26, -(192 + 29)},
	//	{ 192, 192 }
	//);

	//// set action click open new substate
	//myGUIElements.Add(playerPortrait);
	//myGUIElements.Add(textbox);
	//myGUIElements.Add(portrait);
	//myGUIElements.Add(menuButton);
	//myGUILookup["InGame"].myBegin = 0;
	//myGUILookup["InGame"].myEnd = 4;

	//GUIButton* quitButton = new GUIButton();

	//quitButton->Create(
	//	"QuitButton",
	//	"Sprites/GUI/MainMenu/QuitButton/",
	//	{ 0.f, 0.f }, { 1920.f / 2.f, 1080.f / 2.f + 250 }, { 200, 100 });

	//quitButton->SetAction(new GUIMessage(RecieverTypes::eExitGame), eGUIMessageEvents::eOnClick);
	//myGUIElements.Add(quitButton);

	//GUIButton* playButton = new GUIButton();

	//playButton->Create(
	//	"PlayButton",
	//	"Sprites/GUI/MainMenu/PlayButton/",
	//	{ 0.f, 0.f }, { 1920.f / 2.f, 1080.f / 2.f }, { 200, 100 });

	//playButton->SetAction(new GUIMessage(RecieverTypes::ePlayGame), eGUIMessageEvents::eOnClick);
	//myGUIElements.Add(playButton);

	//myGUILookup["MainMenu"].myBegin = 5;
	//myGUILookup["MainMenu"].myEnd = 6;

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