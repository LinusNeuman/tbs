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
	mySprites[USHORTCAST(enumMouseState::eHeldOnEnemy)].Init("Sprites/GUI/MousePointers/EnemyHover.dds", false);
	mySprites[USHORTCAST(enumMouseState::eClickedOnEmptyTile)].Init("Sprites/GUI/MousePointers/ClickedOnEmptyTile.dds", false);
	mySprites[USHORTCAST(enumMouseState::eClickedOnEnemy)].Init("Sprites/GUI/MousePointers/ClickedOnEnemy.dds", false);
	mySprites[USHORTCAST(enumMouseState::eHeldOnVoid)].Init("Sprites/GUI/MousePointers/HeldOnVoid.dds", false);
	mySprites[USHORTCAST(enumMouseState::eClickedOnPlayer)].Init("Sprites/GUI/MousePointers/ClickedOnPlayer.dds", false);
	mySprites[USHORTCAST(enumMouseState::eHeldOnPlayer)].Init("Sprites/GUI/MousePointers/HeldOnPlayer.dds", false);
	mySprites[USHORTCAST(enumMouseState::eHideClickedOnEnemy)].Init("Sprites/GUI/MousePointers/HeldOnVoid.dds", false);
	mySprites[USHORTCAST(enumMouseState::eHideHoverOnEnemy)].Init("Sprites/GUI/MousePointers/HeldOnVoid.dds", false);

	for (unsigned short iSprite = 0; iSprite < mySprites.Size(); ++iSprite)
	{
		mySprites[iSprite].SetLayer(enumRenderLayer::eGUI);
		mySprites[iSprite].SetRenderPriority(9999.f);;
	}
}

void MouseController::SetMouseState(const enumMouseState aMouseStateToChangeTo)
{
	myCurrentState = aMouseStateToChangeTo;
}

void MouseController::Draw(const CU::Vector2f & aNormalizedPosition) const
{
	mySprites[USHORTCAST(myCurrentState)].DrawWithNormalized(aNormalizedPosition);
}