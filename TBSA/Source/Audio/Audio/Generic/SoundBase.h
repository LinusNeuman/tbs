#pragma once
#include "External/fmod.hpp"
#include <string>

enum class eFade
{
	eUp,
	eDown
};

// To avoid static_cast-ing all the time.
template <typename T>
int eFadeInt(T aElementType)
{
	return static_cast<int>(aElementType);
}

// Wraps FMOD Sound class with more functionality
class SoundBase
{
public:
	//				Creation
					SoundBase();
	virtual void	Init(const char* aPath, bool aIsLooped = false) = 0;

	//				Controls
	void			Play(float aVolume);
	void			Pause();
	void			Resume();
	void			Stop();
	void			Fade(eFade aFadeUpOrDown);

	//				Altering
	void			SetLooping(bool aSet);
	void			SetPitch(float aPitch);
	float			GetPitch();
	void			SetVolume(float aVolume);
	float			GetVolume();
	bool			GetIsPlaying();
	bool			GetHasPlayed();

	//				Updates the sound, e.g. fading
	void			Update(float aDeltaTime);

	//				Destruction
	virtual			~SoundBase();
	void			Destroy();
protected:
	// SFX is the actual sound effect that we are wrapping
	// Channel is the way we access/modify this sound after playing it
	// FMOD cant modify sounds, only channels. Every sound has its own channel.

	FMOD::Sound*	mySFX;
	FMOD::Channel*	myChannel;

	std::string		myChannelGroup;

	bool			myIsLooping;
	bool			myHasPlayed;

	bool			myIsFadingUp;
	bool			myIsFadingDown;
	void			FadeDown(float aDeltaTime);
	void			FadeUp(float aDeltaTime);

	// Streams a sound directly from disk.
	void Stream(const char* aFile);

	// Loads a new sound into heap. Use Stream instead.
	void Create(const char* aFile);
};

