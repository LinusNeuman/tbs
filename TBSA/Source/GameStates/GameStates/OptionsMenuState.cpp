#include "stdafx.h"
#include "OptionsMenuState.h"
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

OptionsMenuState::OptionsMenuState()
{
	myLetThroughRender = false;
}


OptionsMenuState::~OptionsMenuState()
{
	SingletonPostMaster::RemoveReciever(*this);
}

void OptionsMenuState::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eCloseOptionsMenu, *this);

	//myBackgroundSprite = new StaticSprite();
	//myBackgroundSprite->Init("Sprites/GUI/OptionsMenu/Background.dds", false, CU::Vector4f::Zero, {0.5f, 0.5f});
	//myBackgroundSprite->SetLayer(enumRenderLayer::eGUI);
	//myBackgroundSprite->SetRenderPriority(2000.f);

	LoadGUI("OptionsMenu");
	myOptionsWrapped.Initialize();
}

eStackReturnValue OptionsMenuState::Update(const CU::Time& aTimeDelta, ProxyStateStack& aStateStack)
{
	myGUIManager.Update(aTimeDelta);

	myOptionsWrapped.Update(aTimeDelta.GetSeconds());

	if (myShouldPop == true || IsometricInput::GetKeyPressed(DIK_ESCAPE) == true)
	{ 
		myShouldPop = false;
		//return eStackReturnValue::ePopSubstate;
		return eStackReturnValue::eDeleteSubstate;
	}

	return eStackReturnValue::eStay;
}

void OptionsMenuState::Draw() const
{
	myGUIManager.Render();

//	myBackgroundSprite->Draw({ SingletonDataHolder::GetTargetResolution().x * 0.5f, SingletonDataHolder::GetTargetResolution().y * 0.5f });

	myOptionsWrapped.Render();
}

bool OptionsMenuState::RecieveMessage(const GUIMessage& aMessage)
{
	if (aMessage.myType == RecieverTypes::eCloseOptionsMenu)
	{
		myShouldPop = true;
	}
	return true;
}
