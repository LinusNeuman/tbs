#include "stdafx.h"
#include "SFXSlider.h"
#include <Audio/AudioManager.h>


SFXSlider::SFXSlider()
{
}

void SFXSlider::InitValue()
{
	AudioManager::GetInstance()->GetChannelGroup("SFX")->getVolume(&myValue);
	SetAllKnobs(ConvertValueToPosition());
	ProgressGet();
}

void SFXSlider::SliderSpecificUpdate()
{
	//SoundManager::GetInstance()->GetChannelGroup("SFX")->setVolume(myValue);
}

void SFXSlider::ProgressGet()
{
	AudioManager::GetInstance()->GetChannelGroup("SFX")->getVolume(&myValue);
}
void SFXSlider::ProgressSet()
{
	AudioManager::GetInstance()->GetChannelGroup("SFX")->setVolume(myValue);
}

SFXSlider::~SFXSlider()
{
}
