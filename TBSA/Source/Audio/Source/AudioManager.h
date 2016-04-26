#pragma once
#include "../External/fmod.hpp"
#include <string>

typedef FMOD::Sound* SoundClass;

class SoundManager
{
public:
	~SoundManager();

	static void CreateInstance()
	{
		if (mySoundManager == nullptr)
		{
			mySoundManager = new SoundManager();
		}
	}

	static SoundManager* const GetInstance()
	{
		if (mySoundManager == nullptr)
		{
			mySoundManager = new SoundManager();
		}
		return mySoundManager;
	}

	static void DestroyInstance()
	{
		if (mySoundManager != nullptr)
		{
			mySoundManager->Destroy();
			delete mySoundManager;
			mySoundManager = nullptr;
		}
	}

	//					Creates a sound on heap memory.
	SoundClass			CreateSound(const char* aFile);
	//					Creates a sound to be streamed from disk.
	SoundClass			CreateStream(const char* aFile);

	//					Get access to a channel containing other channels.
	FMOD::ChannelGroup* GetChannelGroup(const std::string &aName);

	//					Plays a sound that has been created.
	FMOD::Channel*		PlaySound(SoundClass aSound, bool aIsLooping);

	//					Updates the sound system.
	void				Update();
private:
	SoundManager();
	static SoundManager* mySoundManager;

	void Destroy();

	//					The actual FMOD sound system.
	FMOD::System		*mySystem;

	//					The channel groups which holds other channels
	FMOD::ChannelGroup* myChannelGroupMusic;
	FMOD::ChannelGroup* myChannelGroupSFX;

	FMOD::ChannelGroup* myChannelGroupPauseSFX;
	FMOD::ChannelGroup* myChannelGroupPauseMusic;
};

