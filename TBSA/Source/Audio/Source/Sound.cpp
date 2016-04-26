#include "Sound.h"
#include "AudioManager.h"

#pragma region Creation
Sound::Sound()
{
	mySFX = nullptr;
	myChannel = nullptr;

	myIsFadingDown = false;
	myIsFadingUp = false;

	myIsLooping = false;
	myHasPlayed = false;
}

// Creates a sound, provide a path.
void Sound::Init(const char* aPath, bool aIsLooped)
{
	Stream(aPath);
	myIsLooping = aIsLooped;
}

// Loads a new sound into heap. Use Stream instead.
void Sound::Create(const char* aFile)
{
	mySFX = SoundManager::GetInstance()->CreateSound(aFile);
}

// Streams a sound directly from disk.
void Sound::Stream(const char* aFile)
{
	mySFX = SoundManager::GetInstance()->CreateStream(aFile);
}

#pragma endregion

#pragma region Controls
// Plays a sound with given volume
void Sound::Play(float aVolume, eSoundType aSoundType)
{
	bool aBool = false;
	if (myChannel != nullptr)
	{
		myChannel->isPlaying(&aBool);
	}
	if (aBool == false)
	{
		myChannel = SoundManager::GetInstance()->PlaySound(mySFX, myIsLooping);
	}

	switch (aSoundType)
	{
	case eSoundType::eMusic:
		myChannel->setChannelGroup(SoundManager::GetInstance()->GetChannelGroup("Music"));
		break;
	case eSoundType::eSFX:
		myChannel->setChannelGroup(SoundManager::GetInstance()->GetChannelGroup("SFX"));
		break;
	case eSoundType::ePauseSFX:
		myChannel->setChannelGroup(SoundManager::GetInstance()->GetChannelGroup("PauseSFX"));
		break;
	case eSoundType::ePauseMusic:
		myChannel->setChannelGroup(SoundManager::GetInstance()->GetChannelGroup("PauseMusic"));
		break;
	default:
		myChannel->setChannelGroup(SoundManager::GetInstance()->GetChannelGroup("SFX"));
		break;
	}

	myHasPlayed = true;
	
	SetVolume(aVolume);
}

void Sound::Pause()
{
	myChannel->setPaused(true);
}

void Sound::Resume()
{
	myChannel->setPaused(false);
}

void Sound::Stop()
{
	myChannel->stop();
}

void Sound::Fade(eFade aFadeUpOrDown)
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

void Sound::SetLooping(bool aSet)
{
	myIsLooping = aSet;
}

void Sound::SetPitch(float aPitch)
{
	myChannel->setPitch(aPitch);
}

float Sound::GetPitch()
{
	float tempFloat = 0;
	myChannel->getPitch(&tempFloat);
	return tempFloat;
}

void Sound::SetVolume(float aVolume)
{
	myChannel->setVolume(aVolume);
}

float Sound::GetVolume()
{
	float tempFloat = 0;
	myChannel->getVolume(&tempFloat);
	return tempFloat;
}

bool Sound::GetIsPlaying()
{
	bool tempBool = false;
	myChannel->isPlaying(&tempBool);
	return tempBool;
}

bool Sound::GetHasPlayed()
{
	return myHasPlayed;
}
#pragma endregion

#pragma region Update

void Sound::FadeDown(float aDeltaTime)
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
void Sound::FadeUp(float aDeltaTime)
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

void Sound::Update(float aDeltaTime)
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

Sound::~Sound()
{

}

void Sound::Destroy()
{
	mySFX->release();
}

#pragma endregion