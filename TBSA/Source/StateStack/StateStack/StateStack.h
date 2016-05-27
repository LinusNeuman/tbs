#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include "StateStack/GameState.h"
#include "StateStack/ProxyStateStack.h"

#include <GUI/Managing/GUIManager.h>

#pragma warning  (push)
#pragma warning(disable : 4512)

class StateStack
{
public:
	StateStack();
	~StateStack();

	StateStack(StateStack & aStateStack);

	void AddMainState(GameState * aMainState);
	void AddSubState(GameState * aSubstate);

	bool Update(const CU::Time & aDeltaTime);

	void Render() const;

private:
	void PopMainState();
	void PopSubState();
	void PopCurrentSubstates();

	void RenderState(const CU::GrowingArray<GameState *> & aMainState , unsigned short anIndexToCheck) const;

	CU::GrowingArray<CU::GrowingArray<GameState*>> myStates;
	ProxyStateStack myProxy;
};
#pragma warning (pop)