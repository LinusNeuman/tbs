#include "AudioManager.h"
#include <iostream>
#include "../../CommonUtilities/CU/DLDebug/DL_Debug.h"

SoundManager* SoundManager::mySoundManager = nullptr;

#pragma region Creation

SoundManager::SoundManager()
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
	DL_PRINT("Created a sound device");

	mySystem->createChannelGroup("Music_Channel", &myChannelGroupMusic);
	mySystem->createChannelGroup("SFX_Channel", &myChannelGroupSFX);
	mySystem->createChannelGroup("PauseSFX_Channel", &myChannelGroupPauseSFX);
	mySystem->createChannelGroup("PauseMusic_Channel", &myChannelGroupPauseMusic);

	myChannelGroupPauseMusic->setPaused(true);

	myChannelGroupMusic->setVolume(0.8f);
	myChannelGroupPauseMusic->setVolume(0.8f);
}

SoundClass SoundManager::CreateSound(const char* aFile)
{
	// for stream use FMOD_CREATESTREAM
	// FMOD_CREATESAMPLE compresses and streams. FMOD_DEFAULT is higher qual-ish
	SoundClass tempSoundClass = nullptr;
	FMOD_RESULT aRes;
	aRes = mySystem->createSound(aFile, FMOD_2D, 0, &tempSoundClass);
	if (aRes == 18)
	{
		std::string outputstring = "Sound file could not be found. File name was: '" + std::string(aFile) + "'";
		DL_DEBUG(outputstring.c_str());
		std::cout << "Sound file could not be found! File name was: " + std::string(aFile) + " Check empty playsound events" << std::endl;
	}
	return tempSoundClass;
}

SoundClass SoundManager::CreateStream(const char* aFile)
{
	SoundClass tempSoundClass = nullptr;
	FMOD_RESULT aRes;
	aRes = mySystem->createStream(aFile, FMOD_2D, 0, &tempSoundClass);
	if (aRes == 18)
	{
		std::string outputstring = "Stream error: Sound file could not be found. File name was: '" + std::string(aFile) + "'";
		DL_DEBUG(outputstring.c_str());
		std::cout << "Stream error: Sound file could not be found! File name was: " + std::string(aFile) + " Check empty playsound events" << std::endl;
	}
	else if (aRes != FMOD_OK)
	{
		std::string outputstring = "Sound Error: " + std::to_string(aRes) + std::string(". File name was: '") + std::string(aFile) + "'";
		DL_DEBUG(outputstring.c_str());
		std::cout << "Sound Error: " + std::to_string(aRes) + std::string(". File name was: '") + std::string(aFile) + "'" << std::endl;
	}
	return tempSoundClass;
}

#pragma endregion

// Gets a channel group containing other channels.
FMOD::ChannelGroup* SoundManager::GetChannelGroup(const std::string &aName)
{
	if (aName == "Music")
	{
		return myChannelGroupMusic;
	}
	else if (aName == "SFX")
	{
		return myChannelGroupSFX;
	}
	else if (aName == "PauseSFX")
	{
		return myChannelGroupPauseSFX;
	}
	else if (aName == "PauseMusic")
	{
		return myChannelGroupPauseMusic;
	}
	else
	{
		std::cout << "Channel group not found! Tried to get channel group: " << aName << std::endl;
	}
	return nullptr;
}

// Plays a sound that has been created.
FMOD::Channel* SoundManager::PlaySound(SoundClass aSound, bool isLooping)
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
		std::string toPrint;
		toPrint = "Error while trying to play sound: " + std::to_string(res);
		DL_PRINT(toPrint.c_str());
	}

	return tempChannel;
}

// Updates the FMOD sound system.
void SoundManager::Update()
{
	mySystem->update();
}

#pragma region Destruction

SoundManager::~SoundManager()
{

}

void SoundManager::Destroy()
{
	mySystem->close();
	mySystem->release();
}

#pragma endregion