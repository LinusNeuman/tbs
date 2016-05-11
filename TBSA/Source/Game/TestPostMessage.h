#pragma once

#include <Rend/WrappedSprite.h>
#include <MessageReciever.h>

class TestPostMessage : public MessageReciever
{
public:
	TestPostMessage();
	~TestPostMessage();

	void Init();


	virtual void RecieveMessage(const TestPositionMessage aMessage) override;

	void Draw() const;

private:
	WrappedSprite * mySprite;
	CU::Vector2f myPosition;
};
