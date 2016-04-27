#pragma once
#include "../External/fmod.hpp"
#include <string>
#include <unordered_map>

typedef FMOD::Sound* SoundClass;

class AudioManager
{
public:
	~AudioManager();

	static void CreateInstance()
	{
		if (myAudioManager == nullptr)
		{
			myAudioManager = new AudioManager();
		}
	}

	static AudioManager* const GetInstance()
	{
		if (myAudioManager == nullptr)
		{
			myAudioManager = new AudioManager();
		}
		return myAudioManager;
	}

	static void DestroyInstance()
	{
		if (myAudioManager != nullptr)
		{
			myAudioManager->Destroy();
			delete myAudioManager;
			myAudioManager = nullptr;
		}
	}

	//					Creates a sound on heap memory.
	SoundClass			CreateSound(const char* aFile);
	//					Creates a sound to be streamed from disk.
	SoundClass			CreateStream(const char* aFile);

	//					Gets access to a channel containing other channels.
	//					If not found, channelgroup will be created.
	FMOD::ChannelGroup* GetChannelGroup(const std::string &aName);

	//					Plays a sound that has been created.
	FMOD::Channel*		PlaySound(SoundClass aSound, bool aIsLooping);

	//					Updates the sound system.
	void				Update();
private:
	AudioManager();
	static AudioManager* myAudioManager;

	void				Destroy();

	//					The actual FMOD sound system.
	FMOD::System		*mySystem;

	//					The channel groups which holds other channels
	std::unordered_map<std::string, FMOD::ChannelGroup*> myChannelGroups;
};

