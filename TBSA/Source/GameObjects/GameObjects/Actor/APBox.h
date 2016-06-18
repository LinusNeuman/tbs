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

	void CalculateProgress(const CommonUtilities::Time& aTime);
	void MoveUp(const CommonUtilities::Time& aTime);
	void MoveDown(const CommonUtilities::Time& aTime);
	void Animate(const CU::Time& aDelta);

	void __forceinline SetCost(char aAPCost)
	{
		myCurrentCost = aAPCost;
	}

	void __forceinline SetAP(char aAP)
	{
		myAP = aAP;
	};

	void __forceinline SetPos(TilePositionf aPos)
	{
		myAPText->myPosition.x = aPos.x;
		myAPText->myPosition.y = aPos.y;

		myTilePositionf = aPos;
	}

	void Reset();

	void Draw() const;
private:
	char myAP;
	char myCurrentCost;

	StaticSprite* mySprite;
	StaticSprite* mySpriteSelected;
	StaticSprite* mySpriteUnSelected;

	DX2D::CText* myAPText;

	float myEasing;

	eAPBoxState myApBoxState;

	CU::Vector2f myOriginalPosition;
	CU::Vector2f myGoalPosition;

	TilePositionf myTilePositionf;

	CU::Vector2f myPosition;

	CU::Vector4f myColor;
	float myMovementTotalUp;
	float myMovementTotalDown;
	float myMovementTimer;

	CU::Vector2f myOffset;

	bool myIsInitedFully;

	bool myIsSelected;
};