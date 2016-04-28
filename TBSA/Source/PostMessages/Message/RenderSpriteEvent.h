#pragma once

#include "MessageEvent.h"

class WrappedSprite;

class RenderSpriteEvent : public MessageEvent
{
public:
	RenderSpriteEvent();
	~RenderSpriteEvent();

	virtual void DoEvent(RenderConverter & aRenderConverter) override;

private:
	const WrappedSprite & myWrappedSprite;
};

