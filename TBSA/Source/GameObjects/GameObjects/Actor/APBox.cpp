#include "stdafx.h"
#include "APBox.h"
#include <Rend/RenderConverter.h>
#include <Rend/RenderCommand.h>

APBox::APBox()
{
	myAPText = new DX2D::CText("Text/calibril.ttf_sdf");
	mySprite = new StaticSprite();
	mySprite->Init("Sprites/GUI/HUD/AP/ActorAP.dds");
	mySprite->SetLayer(enumRenderLayer::eGUI);
}

APBox::~APBox()
{
	//SAFE_DELETE(myAPText);
	//SAFE_DELETE(mySprite);
}

void APBox::Update()
{
}

void APBox::Draw(TilePositionf aPosition) const
{
	mySprite->Draw(aPosition);

	RenderConverter::AddRenderCommand(RenderCommand(*myAPText, 1.f, static_cast<unsigned short>(enumRenderLayer::eGUI)));
}