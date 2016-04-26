#include "stdafx.h"
#include "TextState.h"
#include "Renderer.h"
#include <ProxyStateStack.h>
#include "InteMartinKakaState.h"

TextState::TextState()
{
}


TextState::~TextState()
{
}

void TextState::Init()
{
	myRenderer = new Renderer();
	myRenderer->Init("Sprites/hestfan.png");
	myRenderer->SetWindowSize(CU::Vector2ui(1280, 720));

	myLetThroughRender = true;

}

eStackReturnValue TextState::Update(const CU::Time & aDeltaTime, ProxyStateStack & aStateStack)
{

	if (GetInput::GetKeyPressed(DIK_A) == true)
	{
		InteMartinKakaState * tempState = new InteMartinKakaState();
		tempState->Init();
		aStateStack.AddSubState(tempState);
	}

	if (GetInput::GetKeyPressed(DIK_END) == true)
	{
		return eStackReturnValue::ePopSubState;
	}
	if (GetInput::GetKeyPressed(DIK_HOME) == true)
	{
		return eStackReturnValue::ePopCurrentSubStates;
	}
	if (GetInput::GetKeyPressed(DIK_DELETE) == true)
	{
		return eStackReturnValue::ePopMain;
	}
	return eStackReturnValue::eStay;
}

void TextState::Draw()
{
	myRenderer->PrintText("TEXTSTATE WHOHHOOO", CU::Vector2f(500.f, 500.f));
}