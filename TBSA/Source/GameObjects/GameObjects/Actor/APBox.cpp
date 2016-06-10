#include "stdafx.h"
#include "APBox.h"


APBox::APBox()
{
	myAPText = new DX2D::CText("0");
	mySprite = new StaticSprite();
	mySprite->Init("Sprites/GUI/HUD/AP/ActorAP.dds");
}


APBox::~APBox()
{
	SAFE_DELETE(myAPText);
	SAFE_DELETE(mySprite);
}

void APBox::Update()
{
}

void APBox::Draw(TilePositionf aPosition)
{
}
