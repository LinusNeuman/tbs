#pragma once
#include <Rend/StaticSprite.h>
#include <tga2d/text/text.h>
#include <CU/Utility/Math/Isometric.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>


typedef unsigned char uchar;

enum class eAPBoxState
{
	eGoingUp,
	eGoingDown
};

class APBox
{
public:
	APBox();
	~APBox();

	void Update();

	void CalculateProgress(const CommonUtilities::Time aTime);
	void MoveUp(const CommonUtilities::Time aTime);
	void MoveDown(const CommonUtilities::Time aTime);
	void Animate(const CU::Time& aDelta);

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

		myTilePositionf = aPos;
	}

	void Reset();

	void Draw() const;
private:
	uchar myAP;

	StaticSprite* mySprite;

	DX2D::CText* myAPText;

	float myEasing;

	eAPBoxState myApBoxState;

	CU::Vector2f myOriginalPosition;
	CU::Vector2f myGoalPosition;

	TilePositionf myTilePositionf;

	CU::Vector2f myPosition;

	float myMovementTotalUp;
	float myMovementTotalDown;
	float myMovementTimer;
};