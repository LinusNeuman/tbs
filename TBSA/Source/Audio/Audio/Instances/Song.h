#pragma once
#include "External/fmod.hpp"
#include <string>
#include <Audio/Generic/SoundBase.h>

// Wraps FMOD Sound class with more functionality
class Song : public SoundBase
{
public:
	//				Creation
					Song();
	void			Init(const char* aPath, bool aIsLooped = false) override;

	//				Destruction
	virtual			~Song();
};

