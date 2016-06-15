#include "stdafx.h"
#include "PreGameState.h"
#include <Rend\RenderConverter.h>

PreGameState::PreGameState() : myTextBox({ 1920.f / 2 - 250, 250.f }, { 1920.f, 1080.f }, "Text/calibril.ttf_sdf", eLinewrappingMode::Word)
{
	myTextBox.SetPosition({ 1920.f / 2 - 250, 250.f });
	myTextBox.SetSize({500.f, 750.f});
	myTextBox.SetLines(50);
	myTextBox.AddText("\"Alright, soldiers\"”, said Curly.");
	myTextBox.AddText("\"The first sign of winter has been spotted. Yesterday I saw Nutty Meg wear the same ugly mittens as every year, so the time has come to prepare\".");
	myTextBox.AddText("Gathered around a crude map of the town, the three of them laid out their battle plan.They would have to lay claim to several key points in town before they could be named the winners of the annual snow-war.");
	myTextBox.AddText("Beneath the treehouse in Curly’s backyard they would hone their skills, Ginger and Long John the footsoldiers on ground, and Curly as their ever watchful commander.");
	myTextBox.AddText("");
	myTextBox.AddText("");
	myTextBox.AddText("");
	myTextBox.AddText("Click to continue...");
	myLetThroughRender = false;
}

PreGameState::~PreGameState()
{
}

eStackReturnValue
PreGameState::Update(const CU::Time& aDeltaTime, ProxyStateStack& aStateStack)
{
	myTextBox.Update();

	if (IsometricInput::GetAnyKeyPressed() == true || IsometricInput::GetAnyMouseButtonPressed() == true)
	{
		return eStackReturnValue::eDeleteSubstate;
	}

	return eStackReturnValue::eStay;
}

void
PreGameState::Draw() const
{
	myTextBox.Render();
}