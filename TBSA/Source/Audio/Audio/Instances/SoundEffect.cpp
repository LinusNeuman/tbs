#include "SoundEffect.h"
#include "../AudioManager.h"

#pragma region Creation

SoundEffect::SoundEffect()
{
	
}


// Creates a sound, provide a path.
void SoundEffect::Init(const char* aPath, bool aIsLooped)
{
	Stream(aPath);
	myIsLooping = aIsLooped;
	myChannelGroup = "SFX";
}

#pragma endregion

#pragma region Destruction

SoundEffect::~SoundEffect()
{

}

#pragma endregion