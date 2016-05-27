#include "AudioManager.h"
#include <iostream>
#include "../../CommonUtilities/CU/DLDebug/DL_Debug.h"

AudioManager* AudioManager::myAudioManager = nullptr;

#pragma region Creation

AudioManager::AudioManager()
{
	if (FMOD::System_Create(&mySystem) != FMOD_OK)
	{
		DL_PRINT("Could not create a sound device.");
		return;
	}

	int driverCount = 0;
	mySystem->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		DL_PRINT("No sound drivers detected.");
		return;
	}

	mySystem->init(36, FMOD_INIT_NORMAL, nullptr);

	system("color B");

	DL_PRINT("Created a sound device");

	GetChannelGroup("SFX")->setVolume(1.0f);
	GetChannelGroup("Song")->setVolume(0.8f);

	system("color");
}

SoundClass AudioManager::CreateSound(const char* aFile)
{
	// for stream use FMOD_CREATESTREAM
	// FMOD_CREATESAMPLE compresses and streams. FMOD_DEFAULT is higher qual-ish
	SoundClass tempSoundClass = nullptr;
	FMOD_RESULT aRes;
	aRes = mySystem->createSound(aFile, FMOD_2D, 0, &tempSoundClass);
	if (aRes == 18)
	{
		system("color B");
		std::string outputstring = "Sound file could not be found. File name was: '" + std::string(aFile) + "'";
		DL_DEBUG(outputstring.c_str());
		std::cout << "Sound file could not be found! File name was: " + std::string(aFile) + " Check empty playsound events" << std::endl;
		system("color");
	}
	return tempSoundClass;
}

SoundClass AudioManager::CreateStream(const char* aFile)
{
	SoundClass tempSoundClass = nullptr;
	FMOD_RESULT aRes;
	aRes = mySystem->createStream(aFile, FMOD_2D, 0, &tempSoundClass);
	if (aRes == 18)
	{
		system("color B");
		std::string outputstring = "Stream error: Sound file could not be found. File name was: '" + std::string(aFile) + "'";
		DL_DEBUG(outputstring.c_str());
		std::cout << "Stream error: Sound file could not be found! File name was: " + std::string(aFile) + " Check empty playsound events" << std::endl;
		system("color");
	}
	else if (aRes != FMOD_OK)
	{
		system("color B");
		std::string outputstring = "Sound Error: " + std::to_string(aRes) + std::string(". File name was: '") + std::string(aFile) + "'";
		DL_DEBUG(outputstring.c_str());
		std::cout << "Sound Error: " + std::to_string(aRes) + std::string(". File name was: '") + std::string(aFile) + "'" << std::endl;
		system("color");
	}
	return tempSoundClass;
}

#pragma endregion

// Gets a channel group containing other channels.
FMOD::ChannelGroup* AudioManager::GetChannelGroup(const std::string &aName)
{
	if (myChannelGroups.find(aName) == myChannelGroups.end())
	{
		FMOD::ChannelGroup* aChannelGroupToAdd = nullptr;
		mySystem->createChannelGroup(aName.c_str(), &aChannelGroupToAdd);
		
		system("color B");
		DL_PRINT(std::string("Created new channel group: " + aName).c_str());
		return myChannelGroups[aName] = aChannelGroupToAdd;
		system("color");
	}

	return myChannelGroups[aName];
}

// Plays a sound that has been created.
FMOD::Channel* AudioManager::PlaySound(SoundClass aSound, bool isLooping)
{
	if (!isLooping)
	{
		aSound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		aSound->setMode(FMOD_LOOP_NORMAL);
		aSound->setLoopCount(-1);
	}

	FMOD::Channel* tempChannel = nullptr;

	FMOD_RESULT res;

	res = mySystem->playSound(aSound, nullptr, false, &tempChannel);

	if (res != FMOD_OK)
	{
		system("color B");
		std::string toPrint;
		toPrint = "Error while trying to play sound: " + std::to_string(res);
		DL_PRINT(toPrint.c_str());
		system("color");
	}

	return tempChannel;
}

// Updates the FMOD sound system.
void AudioManager::Update()
{
	mySystem->update();
}

#pragma region Destruction

AudioManager::~AudioManager()
{

}

void AudioManager::Destroy()
{
	mySystem->close();
	mySystem->release();
}

#pragma endregion