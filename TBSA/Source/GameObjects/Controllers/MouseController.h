#pragma once
#include "Rend\StaticSprite.h"
#include "Controllers\enumMouseState.h"



class MouseController
{
public:
	MouseController();
	~MouseController();

	void SetMouseState(const enumMouseState aMouseStateToChangeTo);

private:
	
	
};