#include "stdafx.h"
#include "StateStack.h"
#include <StateStack/GameState.h>

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
	myStates.GetLast().GetLast()->OnTopStateExit();
	aSubstate->OnTopStateEnter();
	myStates.GetLast().Add(aSubstate);
}

bool StateStack::Update(const CU::Time & aDeltaTime)
{
	switch (myStates.GetLast().GetLast()->Update(aDeltaTime, myProxy))
	{
	/*case eStackReturnValue::ePopMain:
		PopMainState();
		return myStates.Size() > 0;*/
	case eStackReturnValue::eDeleteMainState:
		PopAndDeleteMainState();
		return myStates.Size() > 0;

	/*case eStackReturnValue::ePopCurrentSubStates:
		PopCurrentSubstates();
		return true;*/
	case eStackReturnValue::eDeleteCurrentSubstates:
		PopAndDeleteCurrentSubstates();
		return true;

	case eStackReturnValue::eDeleteSubstate:
		PopAndDeleteSubstate();
		return true;
	/*case eStackReturnValue::ePopSubState:
		PopSubState();*/
	case eStackReturnValue::eStay:
		return true;
	}
	return false;
}

void StateStack::Render() const
{
	RenderState(myStates.GetLast(), myStates.GetLast().Size() -1);
}


void StateStack::PopAndDeleteSubstate()
{
	DL_ASSERT(myStates.GetLast().Size() > 1, "GameStateStack - Trying to pop a substate when there are none!");
	myStates.GetLast().DeleteCyclicAtIndex(myStates.GetLast().Size() - 1);	
}

void StateStack::PopAndDeleteCurrentSubstates()
{
	for (unsigned short iSubState = myStates.GetLast().Size() - 1; iSubState > 0; --iSubState)
	{
		PopAndDeleteSubstate();
	}
}

void StateStack::PopAndDeleteMainState()
{
	DL_ASSERT(myStates.Size() > 0, "GameStateStack - Trying to pop a mainstate when there are none!");
	PopAndDeleteCurrentSubstates();
	myStates.GetLast().DeleteCyclicAtIndex(0);
	myStates.RemoveAtIndex(myStates.Size() - 1);
}

void StateStack::PopMainState()
{
	DL_ASSERT(myStates.Size() > 0, "GameStateStack - Trying to pop a mainstate when there are none!");
	myStates.RemoveAtIndex(myStates.Size() - 1);
}

void StateStack::PopSubState()
{
	DL_ASSERT(myStates.GetLast().Size() > 1, "GameStateStack - Trying to pop a substate when there are none!");
	myStates.GetLast().RemoveAtIndex(myStates.GetLast().Size() - 1);
}

void StateStack::PopCurrentSubstates()
{
	for (unsigned short iSubState = myStates.GetLast().Size() - 1; iSubState > 0; --iSubState)
	{
		PopSubState();
	}
}

void StateStack::RenderState(const CU::GrowingArray<GameState *> & aMainState, unsigned short anIndexToCheck) const
{
	if (aMainState[anIndexToCheck]->GetShouldLetThroughRendering() == true && anIndexToCheck > 0)
	{
		RenderState(aMainState, anIndexToCheck - 1);
	}
	aMainState[anIndexToCheck]->Draw();
}
