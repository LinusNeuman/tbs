#include "stdafx.h"
#include "TestPostMessage.h"
#include <SingletonPostMaster.h>

TestPostMessage::TestPostMessage()
{
	mySprite = new WrappedSprite();
	myPosition = CU::Vector2f(3.f, 3.f);
}


TestPostMessage::~TestPostMessage()
{
}

void TestPostMessage::Init()
{
	mySprite->Init("Sprites/tga_logo.dds");
	SingletonPostMaster::AddReciever(RecieverTypes::ePlayer, *this);
}

void TestPostMessage::RecieveMessage(const TestPositionMessage aMessage)
{
	myPosition = aMessage.myPosition;
}

void TestPostMessage::Draw() const
{
	mySprite->Draw(myPosition);
}