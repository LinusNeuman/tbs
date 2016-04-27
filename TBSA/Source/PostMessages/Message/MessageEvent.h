#pragma once
class MessageEvent
{
public:
	MessageEvent();
	virtual ~MessageEvent();

	virtual void DoEvent(RenderConverter & aRenderConverter);
};