 #include "GUIFactory.h"
#include <iostream>

#include <CU/Timer/Timer.h>
#include <CU/Timer/TimeManager.h>
#include <GUI/Instances/GUIButton.h>
#include <GUI/Instances/GUIDialog.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>
#include <GUI/Instances/GUIActionPointsBar.h>
#include <GUI/Instances/GUIChangePlayerButton.h>
#include <Message\LevelChangeMassage.h>
#include <Message\CreditScreenMessage.h>
#include <GUI/Instances/GUIPortraitActive.h>
#include <GUI/Instances/GUIActionPeek.h>
#include <GUI/Instances/GUIObjectiveDialog.h>

GUIFactory* GUIFactory::myInstance = nullptr;

//#define VIRTUALSCREENWIDTH 19-20.f
//#define VIRTUALSCREENHEIGHT 10-80.f

GUIFactory::GUIFactory()
{
}


GUIFactory::~GUIFactory()
{
	myGUIElements.DeleteAll();
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

		if (currentStateName == "InGame")
		{
			GUIDialog* dialogTextBox = new GUIDialog({ 15.f/*808.f*/, 15.f/*832.f*/ }, { 381.f, 214.f }, "Text/calibril.ttf_sdf", eLinewrappingMode::Word);
			dialogTextBox->SetLines(7);
			myGUIElements.Add(dialogTextBox);

			GUIObjectiveDialog* objectiveTextBox = new GUIObjectiveDialog({1920 - 381 - 15.f, 15.f}, {381.f, 214.f}, "Text/calibril.ttf_sdf", eLinewrappingMode::Word);
			objectiveTextBox->SetLines(7);
			myGUIElements.Add(objectiveTextBox);

			CU::Vector2f position;
			position.x = 25;
			position.y = 785;
			position.x /= 1920;
			position.y /= 1080;

			position.x *= SingletonDataHolder::GetTargetResolution().x;
			position.y *= SingletonDataHolder::GetTargetResolution().y;

			GUIChangePlayerButton* changePlayerButton = new GUIChangePlayerButton();
			changePlayerButton->Create("ChangeSelectedPlayerButton", "Sprites/GUI/InGame/PortraitChangeButton", CU::Vector2f::Zero, position, { 85, 68 }, true, true, true, false, true);

			myGUIElements.Add(changePlayerButton);

			position.x = 25;
			position.y = 859;
			position.x /= 1920;
			position.y /= 1080;

			position.x *= SingletonDataHolder::GetTargetResolution().x;
			position.y *= SingletonDataHolder::GetTargetResolution().y;

			GUIPortraitActive* portraitActive = new GUIPortraitActive();
			portraitActive->Create("PortraitActive", "Sprites/GUI/InGame/PortraitIconActive", {0,0}, position, { 192, 192 }, true, true, true, false, true);

			myGUIElements.Add(portraitActive);

			position.x = 25;
			position.y = 695;

			position.x /= 1920;
			position.y /= 1080;

			position.x *= SingletonDataHolder::GetTargetResolution().x;
			position.y *= SingletonDataHolder::GetTargetResolution().y;

			GUIPortraitPassive* newPortraitPassive = new GUIPortraitPassive();

			newPortraitPassive->Create("PassivePortraitIcon", "Sprites/GUI/InGame/PortraitIconPassive", CU::Vector2f::Zero, position, { 85, 85 }, true, true, true, false, true);

			myGUIElements.Add(newPortraitPassive);

			GUIActionPeek* newPeek = new GUIActionPeek();
			newPeek->Init();

			myGUIElements.Add(newPeek);

			++elementsAdded;
			++elementsAdded;
			++elementsAdded;
			++elementsAdded;
			++elementsAdded;

			myGUILookup["InGame"].myEnd = elementsAdded;

			++elementsAdded;
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

					CU::Vector2f position = myJSON.GetVector2f("myPositionX", "myPositionY", arrayElements[j].get<picojson::object>());

					position.x /= 1920;
					position.y /= 1080;

					position.x *= SingletonDataHolder::GetTargetResolution().x;
					position.y *= SingletonDataHolder::GetTargetResolution().y;

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
					if (name == "BackButton")
					{
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
							enabled,
							2100.f
							);
					}
					else
					{
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
					}
					

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

					if (clickEvent == "ClosePauseMenu")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eClosePauseMenu), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "Restart")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eRestartLevel), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "GameOverRestart")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eGameOverReset), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "LevelSelect")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eLevelSelect), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "SelectLevel1")
					{
						newButton->SetAction(new LevelChangeMassage(RecieverTypes::eGoToLevel, 1), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "SelectLevel2")
					{
						newButton->SetAction(new LevelChangeMassage(RecieverTypes::eGoToLevel, 2), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "SelectLevel3")
					{
						newButton->SetAction(new LevelChangeMassage(RecieverTypes::eGoToLevel, 3), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "SelectLevel4")
					{
						newButton->SetAction(new LevelChangeMassage(RecieverTypes::eGoToLevel, 4), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "SelectLevel5")
					{
						newButton->SetAction(new LevelChangeMassage(RecieverTypes::eGoToLevel, 5), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "SelectLevel6")
					{
						newButton->SetAction(new LevelChangeMassage(RecieverTypes::eGoToLevel, 6), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "GoToCredits")
					{
						newButton->SetAction(new CreditScreenMessage(RecieverTypes::eGoToCredits), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "GoToMainMenu")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eGoToMainMenu), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "OpenOptionsMenu")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eOpenOptionsMenu), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "CloseOptionsMenu")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eCloseOptionsMenu), eGUIMessageEvents::eOnClick);
					}

					if (clickEvent == "EndScreenContinue")
					{
						newButton->SetAction(new GUIMessage(RecieverTypes::eContinueEndScreen), eGUIMessageEvents::eOnClick);
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