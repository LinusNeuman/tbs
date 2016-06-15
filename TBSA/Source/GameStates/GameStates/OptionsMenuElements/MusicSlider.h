#pragma once
#include "Slider.h"
class MusicSlider :
	public Slider
{
public:
	MusicSlider();

	void InitValue() override;
	void SliderSpecificUpdate() override;
	void ProgressSet() override;
	void ProgressGet() override;

	~MusicSlider();
};

