#include "stdafx.h"
#include "StateStack.h"

StateStack::StateStack() : myProxy(*this)
{
	myStates.Init(5);
}

StateStack::StateStack(StateStack & aStateStack) : myProxy(*this)
{
	myStates = aStateStack.myStates;
}

StateStack::~StateStack()
{
}


void StateStack::AddMainState(GameState * aMainState)
{
	CU::GrowingArray<GameState*> tempMainState;
	tempMainState.Init(1);
	myStates.Add(tempMainState);
	AddSubState(aMainState);
}

void StateStack::AddSubState(GameState * aSubstate)
{
	myStates.GetLast().Add(aSubstate);
}

bool StateStack::Update(const CU::Time & aDeltaTime)
{
	switch (myStates.GetLast().GetLast()->Update(aDeltaTime, myProxy))
	{
	case eStackReturnValue::ePopMain:
		PopMainState();
		return myStates.Size() > 0;
	case eStackReturnValue::ePopCurrentSubStates:
		PopCurrentSubstates();
		return true;
	case eStackReturnValue::ePopSubState:
		PopSubState();
	case eStackReturnValue::eStay:
		return true;
	}
	return false;
}

void StateStack::Render()
{
	RenderState(myStates.GetLast(), myStates.GetLast().Size() -1);
}


void StateStack::PopMainState()
{
	DL_ASSERT(myStates.Size() > 0, "GameStateStack - Trying to pop a mainstate when there are none!");
	myStates.RemoveAtIndex(myStates.Size() - 1);
}

void StateStack::PopSubState()
{
	DL_ASSERT(myStates.GetLast().Size() > 0, "GameStateStack - Trying to pop a substate when there are none!");
	myStates.GetLast().RemoveAtIndex(myStates.GetLast().Size() - 1);
}

void StateStack::PopCurrentSubstates()
{
	for (unsigned short iSubState = myStates.GetLast().Size() - 1; iSubState > 0; --iSubState)
	{
		PopSubState();
	}
}

void StateStack::RenderState(CU::GrowingArray<GameState *> & aMainState, unsigned short anIndexToCheck)
{
	if (aMainState[anIndexToCheck]->GetShouldLetThroughRendering() == true && anIndexToCheck > 0)
	{
		RenderState(aMainState, anIndexToCheck - 1);
	}
	aMainState[anIndexToCheck]->Draw();
}
