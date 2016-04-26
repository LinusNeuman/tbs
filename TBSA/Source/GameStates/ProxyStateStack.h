#pragma once

class GameState;
class StateStack;

class ProxyStateStack
{
public:
	ProxyStateStack(StateStack & aStateStack);
	~ProxyStateStack();

	void AddMainState(GameState * aMainState);
	void AddSubState(GameState * aSubState);

private:
	StateStack & myStateStack;
};