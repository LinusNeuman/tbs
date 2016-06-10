#pragma once
#include <Rend/StaticSprite.h>
#include <tga2d/text/text.h>

typedef unsigned char uchar;

class APBox
{
public:
	APBox();
	~APBox();

	void Update();

	void Draw(TilePositionf aPosition);
private:
	uchar myAP;

	StaticSprite* mySprite;

	DX2D::CText* myAPText;
};