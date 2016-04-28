#pragma once
class GameState;
class StateStack;
#pragma warning  (push)
#pragma warning(disable : 4512)
class ProxyStateStack
{

public:
	ProxyStateStack(StateStack & aStateStack);
	~ProxyStateStack();
	void AddMainState(GameState * aMainState);
	void AddSubState(GameState * aSubState);

private:
	StateStack &myStateStack;
};
#pragma warning (pop)
