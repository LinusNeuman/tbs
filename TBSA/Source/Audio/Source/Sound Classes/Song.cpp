#include "Song.h"
#include "../AudioManager.h"

#pragma region Creation

Song::Song()
{
	
}


// Creates a sound, provide a path.
void Song::Init(const char* aPath, bool aIsLooped)
{
	Stream(aPath);
	myIsLooping = aIsLooped;
	myChannelGroup = "Song";
}

#pragma endregion

#pragma region Destruction

Song::~Song()
{

}

#pragma endregion