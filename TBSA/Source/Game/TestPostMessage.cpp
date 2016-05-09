#include "stdafx.h"
#include "TestPostMessage.h"


TestPostMessage::TestPostMessage()
{
	mySprite = new WrappedSprite();
}


TestPostMessage::~TestPostMessage()
{
}

void TestPostMessage::Init()
{
	mySprite->Init();
}

void TestPostMessage::RecieveMessage(const TestPositionMessage aMessage)
{
	throw std::logic_error("The method or operation is not implemented.");
}

