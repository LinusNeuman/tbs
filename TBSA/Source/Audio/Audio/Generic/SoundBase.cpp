#include "SoundBase.h"
#include "../AudioManager.h"

#pragma region Creation
SoundBase::SoundBase()
{
	mySFX = nullptr;
	myChannel = nullptr;

	myIsFadingDown = false;
	myIsFadingUp = false;

	myIsLooping = false;
	myHasPlayed = false;

	myChannelGroup = "undefined";
}

// Creates a sound, provide a path.
void SoundBase::Init(const char* aPath, bool aIsLooped)
{
	Stream(aPath);
	myIsLooping = aIsLooped;
}

// Loads a new sound into heap. Use Stream instead.
void SoundBase::Create(const char* aFile)
{
	mySFX = AudioManager::GetInstance()->CreateSound(aFile);
}

// Streams a sound directly from disk.
void SoundBase::Stream(const char* aFile)
{
	mySFX = AudioManager::GetInstance()->CreateStream(aFile);
}

#pragma endregion

#pragma region Controls
// Plays a sound with given volume
void SoundBase::Play(float aVolume)
{
	bool aBool = false;
	if (myChannel != nullptr)
	{
		myChannel->isPlaying(&aBool);
	}
	if (aBool == false)
	{
		myChannel = AudioManager::GetInstance()->PlaySound(mySFX, myIsLooping);
	}

	myChannel->setChannelGroup(AudioManager::GetInstance()->GetChannelGroup(myChannelGroup));

	myHasPlayed = true;
	
	SetVolume(aVolume);
}

void SoundBase::Pause()
{
	myChannel->setPaused(true);
}

void SoundBase::Resume()
{
	myChannel->setPaused(false);
}

void SoundBase::Stop()
{
	myChannel->stop();
}

void SoundBase::Fade(eFade aFadeUpOrDown)
{
	if (eFadeInt(aFadeUpOrDown) == 0)
	{
		myIsFadingDown = false;
		myIsFadingUp = true;
	}
	else if (eFadeInt(aFadeUpOrDown) == 1)
	{
		myIsFadingDown = true;
		myIsFadingUp = false;
	}
}

#pragma endregion

#pragma region Altering

void SoundBase::SetLooping(bool aSet)
{
	myIsLooping = aSet;
}

void SoundBase::SetPitch(float aPitch)
{
	myChannel->setPitch(aPitch);
}

float SoundBase::GetPitch()
{
	float tempFloat = 0;
	myChannel->getPitch(&tempFloat);
	return tempFloat;
}

void SoundBase::SetVolume(float aVolume)
{
	myChannel->setVolume(aVolume);
}

float SoundBase::GetVolume()
{
	float tempFloat = 0;
	myChannel->getVolume(&tempFloat);
	return tempFloat;
}

bool SoundBase::GetIsPlaying()
{
	bool tempBool = false;
	myChannel->isPlaying(&tempBool);
	return tempBool;
}

bool SoundBase::GetHasPlayed()
{
	return myHasPlayed;
}
#pragma endregion

#pragma region Update

void SoundBase::FadeDown(float aDeltaTime)
{
	float volume;
	myChannel->getVolume(&volume);

	if (volume > 0.0f)
	{
		volume -= 0.001f * aDeltaTime;
		myChannel->setVolume(volume);
		myChannel->getVolume(&volume);
		if (volume < 0)
		{
			myIsFadingDown = false;
			myChannel->setVolume(0.0f);
		}
	}
}
void SoundBase::FadeUp(float aDeltaTime)
{
	float volume;
	myChannel->getVolume(&volume);

	if (volume < 1.1f)
	{
		volume += 0.001f * aDeltaTime;
		myChannel->setVolume(volume);
		myChannel->getVolume(&volume);
		if (volume > 1)
		{
			myIsFadingUp = false;
			myChannel->setVolume(1.0f);
		}
	}
}

void SoundBase::Update(float aDeltaTime)
{
	if (myIsFadingDown == true)
	{
		FadeDown(aDeltaTime);
	}
	if (myIsFadingUp == true)
	{
		FadeUp(aDeltaTime);
	}
	float aVol;
	myChannel->getVolume(&aVol);
}

#pragma endregion

#pragma region Destruction

SoundBase::~SoundBase()
{

}

void SoundBase::Destroy()
{
	mySFX->release();
}

#pragma endregion