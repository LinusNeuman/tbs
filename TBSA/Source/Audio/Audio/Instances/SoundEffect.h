#pragma once
#include "External/fmod.hpp"
#include <string>
#include <Audio/Generic/SoundBase.h>

// Wraps FMOD Sound class with more functionality
class SoundEffect : public SoundBase
{
public:
	//				Creation
					SoundEffect();
	void			Init(const char* aPath, bool aIsLooped = false) override;

	//				Destruction
	virtual			~SoundEffect();
};

