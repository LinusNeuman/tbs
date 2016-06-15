#pragma once
#include "Rend\StaticSprite.h"
#include "Controllers\enumMouseState.h"

class MouseController
{
public:
	MouseController();
	~MouseController();

	void Init();

	void SetMouseState(const enumMouseState aMouseStateToChangeTo);

	void Draw(const CU::Vector2f & aNormalizedPosition) const;



private:
	enumMouseState myCurrentState;
	CU::GrowingArray<StaticSprite> mySprites;
};