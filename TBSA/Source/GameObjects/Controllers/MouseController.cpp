#include "stdafx.h"
#include "MouseController.h"


MouseController::MouseController()
{
	myCurrentState = enumMouseState::eHeldOnEmptyTile;
}


MouseController::~MouseController()
{
}

void MouseController::Init()
{
	mySprites.Init(USHORTCAST(enumMouseState::enumLength));
	mySprites.Resize(USHORTCAST(enumMouseState::enumLength));

	mySprites[USHORTCAST(enumMouseState::eHeldOnEmptyTile)].Init("Sprites/GUI/MousePointers/EmptyTileHover.dds", false);
	//mySprites[USHORTCAST(enumMouseState::e)].Init("Sprites/GUI/MousePointers/EmptyTileHover.dds", false);

	for (unsigned short iSprite = 0; iSprite < mySprites.Size(); ++iSprite)
	{
		mySprites[iSprite].SetLayer(enumRenderLayer::eGUI);
		mySprites[iSprite].SetRenderPriority(9999.f);;
	}
}

void MouseController::Draw(const CU::Vector2f & aNormalizedPosition) const
{
	mySprites[USHORTCAST(myCurrentState)].DrawWithNormalized(aNormalizedPosition);
}