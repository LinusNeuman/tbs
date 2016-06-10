#pragma once
#include <Rend/StaticSprite.h>
#include <tga2d/text/text.h>
#include <CU/Utility/Math/Isometric.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>


typedef unsigned char uchar;

class APBox
{
public:
	APBox();
	~APBox();

	void Update();
	void __forceinline SetAP(uchar aAP)
	{
		myAP = aAP;
		myAPText->myText = std::to_string(myAP);
	};

	void __forceinline SetPos(TilePositionf aPos)
	{
		CU::Vector2f tempPos = CU::IsometricToPixel(aPos);
		tempPos.x /= SingletonDataHolder::GetTargetResolution().x;
		tempPos.y /= SingletonDataHolder::GetTargetResolution().y;

		myAPText->myPosition.x = tempPos.x;
		myAPText->myPosition.y = tempPos.y;
	}

	void Draw(TilePositionf aPosition) const;
private:
	uchar myAP;

	StaticSprite* mySprite;

	DX2D::CText* myAPText;
};