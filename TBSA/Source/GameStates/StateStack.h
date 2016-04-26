#pragma once
#include "GameState.h"
#include <CU/GrowingArray/GrowingArray.h>
#include "ProxyStateStack.h"


class StateStack
{
public:
	StateStack();
	~StateStack();

	StateStack(StateStack & aStateStack);

	void AddMainState(GameState * aMainState);
	void AddSubState(GameState * aSubstate);

	bool Update(const CU::Time & aDeltaTime);

	void Render();

private:
	void PopMainState();
	void PopSubState();
	void PopCurrentSubstates();

	void RenderState(CU::GrowingArray<GameState *> & aMainState , unsigned short anIndexToCheck);

	CU::GrowingArray<CU::GrowingArray<GameState*>> myStates;
	ProxyStateStack myProxy;
};

