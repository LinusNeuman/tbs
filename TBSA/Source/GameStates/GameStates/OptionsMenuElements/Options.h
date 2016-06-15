#pragma once
#include "SFXSlider.h"
#include "MusicSlider.h"
#include <Rend/StaticSprite.h>

class Options
{
public:
	Options();

	void Initialize();
	void Update(float aDeltaTime);
	void Render() const;

	~Options();
private:
	StaticSprite* myBackground;
	CU::Vector2f myPosition;

	MusicSlider myMusicSlider;
	SFXSlider mySFXSlider;

	bool myMouseWasInvisible;
	bool myIsActive;
};

