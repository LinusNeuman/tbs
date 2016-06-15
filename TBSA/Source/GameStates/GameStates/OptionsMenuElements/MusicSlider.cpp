#include "stdafx.h"
#include "MusicSlider.h"
#include <Audio/AudioManager.h>
#include <iostream>

MusicSlider::MusicSlider()
{
}

void MusicSlider::InitValue()
{
	AudioManager::GetInstance()->GetChannelGroup("Song")->getVolume(&myValue);
}

void MusicSlider::SliderSpecificUpdate()
{
	
}

void MusicSlider::ProgressGet()
{
	AudioManager::GetInstance()->GetChannelGroup("Song")->getVolume(&myValue);
	//std::cout << "Music volume: " << myValue << std::endl;
}
void MusicSlider::ProgressSet()
{
	AudioManager::GetInstance()->GetChannelGroup("Song")->setVolume(myValue);
}

MusicSlider::~MusicSlider()
{
}
