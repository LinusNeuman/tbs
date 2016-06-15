#pragma once
#include "Slider.h"
class SFXSlider :
	public Slider
{
public:
	SFXSlider();

	void InitValue() override;
	void SliderSpecificUpdate() override;
	void ProgressSet() override;
	void ProgressGet() override;

	~SFXSlider();
};

