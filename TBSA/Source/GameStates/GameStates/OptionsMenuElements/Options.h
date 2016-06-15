#pragma once
#include "tga2d\sprite\sprite.h"
#include "SFXSlider.h"
#include "MusicSlider.h"

class Options
{
public:
	Options();

	void Initialize();
	void Update(float aDeltaTime);
	void Render() const;

	~Options();
private:
	DX2D::CSprite* myBackground;

	MusicSlider myMusicSlider;
	SFXSlider mySFXSlider;

	bool myMouseWasInvisible;
	bool myIsActive;
};

