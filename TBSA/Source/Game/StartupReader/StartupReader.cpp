#include "stdafx.h"
#include "StartupReader.h"
#include <JsonWrapper/JsonWrapper.h>
#include <Pico/picojson.h>
#include "StartupReader/StartupData.h"


StartupReader::StartupReader()
{
	myJsonWrapper = new JsonWrapper();
}


StartupReader::~StartupReader()
{
	SAFE_DELETE(myJsonWrapper);
}

StartupData StartupReader::LoadAndGetStartupData()
{
	picojson::value settingsRoot = myJsonWrapper->LoadPicoValue("Data/StartupSettings/StartupSettings.json");
	picojson::object objectOfRoot = myJsonWrapper->GetPicoObject(settingsRoot);
	picojson::object resolutionObject = myJsonWrapper->GetPicoObject(settingsRoot.get("ResolutionSettings"));


	StartupData tempData;

	tempData.myWindowWidth = static_cast<unsigned short>(myJsonWrapper->GetInt("X", resolutionObject));
	tempData.myWindowHeight = static_cast<unsigned short>(myJsonWrapper->GetInt("Y", resolutionObject));

	tempData.myFullScreenFlag = myJsonWrapper->GetBool("IsFullscreen", objectOfRoot);

	return tempData;
}