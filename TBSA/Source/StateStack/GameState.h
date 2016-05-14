#pragma once
#include <CU/Timer/Time.h>
#include <CU/NameSpaceAliases.h>
#include "../GUI/GUI/Generic/GUIElement.h"

class ProxyStateStack;

enum class eStackReturnValue
{
	eStay,
	ePopMain,
	ePopSubState,
	ePopCurrentSubStates
};


class GameState
{
public:
	GameState(const char* aName);
	virtual ~GameState();

	virtual void Init();
	
	virtual eStackReturnValue Update(const CU::Time & aDeltaTime, ProxyStateStack & aStateStack) = 0;
	virtual void Draw() const = 0;

	bool GetShouldLetThroughRendering();

protected:
	bool myLetThroughRender;

	CU::GrowingArray<GUIElement*, uchar> myGUIElements;

	const char* myName;
};