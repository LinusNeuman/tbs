#pragma once
#include <CU/Timer/Time.h>
#include <CU/NameSpaceAliases.h>
#include <GUI/Generic/GUIElement.h>
#include <GUI/Managing/GUIManager.h>

class ProxyStateStack;

enum class eStackReturnValue
{
	eStay,
	/*ePopMain,
	ePopSubState,*/
	eDeleteMainState,
	eDeleteSubstate,
	eDeleteCurrentSubstates,
	//ePopCurrentSubStates
};

class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void Init();
	virtual void OnTopStateEnter();
	virtual void OnTopStateExit();

	void LoadGUI(const char* aName);

	virtual eStackReturnValue Update(const CU::Time & aDeltaTime, ProxyStateStack & aStateStack) = 0;
	virtual void Draw() const = 0;

	bool GetShouldLetThroughRendering();

protected:
	bool myLetThroughRender;

	GUIManager myGUIManager;
};