#include "stdafx.h"
#include "ProxyStateStack.h"
#include "StateStack.h"


ProxyStateStack::ProxyStateStack(StateStack & aStateStack) : myStateStack(aStateStack)
{
}


ProxyStateStack::~ProxyStateStack()
{
}

void ProxyStateStack::AddMainState(GameState * aMainState)
{
	myStateStack.AddMainState(aMainState);
}

void ProxyStateStack::AddSubState(GameState * aSubState)
{
	myStateStack.AddSubState(aSubState);
}
