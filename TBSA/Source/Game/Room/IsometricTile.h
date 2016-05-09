#pragma once
#include <Rend/WrappedSprite.h>

class IsometricTile
{
public:
	IsometricTile();
	IsometricTile(const CU::Vector2f & aPosition);
	~IsometricTile();

	void Init();

	void Draw() const;

private:
	CU::Vector2f myPosition;
	WrappedSprite * mySprite;
};