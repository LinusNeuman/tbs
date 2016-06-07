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

		if (arrayElements.empty() == false)
		{
			myGUILookup[currentStateName].myBegin = elementsAdded;
		}

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


					const std::string imagePath = myJSON.GetString("myImagesPath", arrayElements[j].get<picojson::object>());

					const CU::Vector2f position = myJSON.GetVector2f("myPositionX", "myPositionY", arrayElements[j].get<picojson::object>());

					const CU::Vector2f size = myJSON.GetVector2f("mySizeX", "mySizeY", arrayElements[j].get<picojson::object>());

					const bool shouldPlayClickSound = myJSON.GetBool("myShouldPlayClickSound", arrayElements[j].get<picojson::object>());

					const bool enabled = myJSON.GetBool("myIsEnabled", arrayElements[j].get<picojson::object>());

					const bool isometric = myJSON.GetBool("myIsIsometric", arrayElements[j].get<picojson::object>());

					const bool animated = myJSON.GetBool("myAnimated", arrayElements[j].get<picojson::object>());

					const bool shouldplayclick = myJSON.GetBool("myShouldPlayClickSound", arrayElements[j].get<picojson::object>());

					const bool shouldplayhover = myJSON.GetBool("myShouldPlayHoverSound", arrayElements[j].get<picojson::object>());

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
						animated,
						shouldplayclick,
						shouldplayhover,
						isometric,
						enabled
					);

					// also add tooltip 

					if (clickEvent == "EndTurn")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eEndTurn), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "ExitGame")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eExitGame), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "PlayGame")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::ePlayGame), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "OpenPauseMenu")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eOpenPauseMenu), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "Restart")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eGameOverReset), eGUIMessageEvents::eOnClick);
					}


					myGUIElements.Add(newButton);
					myGUILookup[currentStateName].myEnd = elementsAdded;

					++elementsAdded;
		}
	}

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