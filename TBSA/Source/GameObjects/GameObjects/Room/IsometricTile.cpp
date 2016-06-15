#include "stdafx.h"
#include "IsometricTile.h"
#include <Rend/StaticSprite.h>
#include <NavGraph/Vertex/NavVertex.h>

IsometricTile::IsometricTile(): IsometricTile(CommonUtilities::Point2f::Zero)
{
}

IsometricTile::IsometricTile(const CommonUtilities::Vector2f & aPosition)
{
	myPosition = aPosition;
	myGraphicsLayers.Init(1);
	myState = eTileState::NONE;
	myDebugMode = false;
	myIsVisible = false;
	myIsDiscovered = false;
	myIsInEnemyFoV = false;
	myEnemy = nullptr;
	myAvailableDirections.Init(8);
	myHasCandy = false;
	for (size_t i = 1; i < 9; i++)
	{
		myAvailableDirections.Add(static_cast<eDirection>(i * 10));
	}

	myObjectiveSprites[0] = nullptr;
	myObjectiveSprites[1] = nullptr;
	myCurrentObjectiveSprite = 0;
}

IsometricTile::~IsometricTile()
{
}

void IsometricTile::Init()
{
	
}

void IsometricTile::Draw() const
{
	CommonUtilities::Vector4f currentColour = CommonUtilities::Vector4f(1, 1, 1, 1);

	if (myDebugMode == true)
	{
		switch (myType)
		{
		case eTileType::EMPTY:
			currentColour = CommonUtilities::Vector4f(1.f, 1.f, 1.f, .5f);
			break;
		case eTileType::OPEN:
			currentColour = CommonUtilities::Vector4f(0.f, 1.f, 0.f, 1.f);
			break;
		case eTileType::BLOCKED:
			currentColour = CommonUtilities::Vector4f(1.f, 0.f, 0.f, 1.f);
			break;
		case eTileType::DOOR:
			currentColour = CommonUtilities::Vector4f(1.f, .7f, 0.f, 1.f);
			break;
		case eTileType::DOOR_2:
			currentColour = CommonUtilities::Vector4f(1.f, .9f, 0.f, 1.f);
			break;
		case eTileType::IS_OBJECTIVE:
			currentColour = CommonUtilities::Vector4f(1.0f, 0.54f, 0.f, 1.0f);
			break;
		case eTileType::Size: break;
		default: break;
		}
	}

	switch (myState)
	{
	case eTileState::IN_RANGE:
		currentColour = CommonUtilities::Vector4f(0, 0, 1, 1);
		break;
	case eTileState::IN_PATH:
		currentColour = CommonUtilities::Vector4f(1, 1, 0, 1);
		break;
	case eTileState::UNDER_MOUSE:
		currentColour = CommonUtilities::Vector4f(0, 1, 1, 1);
		break;
	case eTileState::IS_WALKABLE:
	case eTileState::NONE:
	case eTileState::Size:
	default:
	break;
	}

	if (CheckHasCandy() == true)
	{
		currentColour = CommonUtilities::Vector4f(1.f, 0.73f, 0.85f, 1);
	}


	for (USHORT i = 0; i < myGraphicsLayers.Size(); i++)
	{
		if (myDebugMode == true)
		{
			myGraphicsLayers[i]->SetColor(currentColour);
		}
		else if (myGraphicsLayers[i]->GetColor() != CommonUtilities::Vector4f(1, 1, 1, 1))
		{
			myGraphicsLayers[i]->SetColor(CommonUtilities::Vector4f(1, 1, 1, 1));
		}
		CommonUtilities::Vector2f positionModifier = CommonUtilities::Vector2f::Zero;
		if (myGraphicsLayers[i]->GetLayer() == enumRenderLayer::eFloor)
		{
			positionModifier += CommonUtilities::Vector2f(1, 1);
		}

		myGraphicsLayers[i]->Draw(myPosition + positionModifier);
	}

	if (myObjectiveSprites[myCurrentObjectiveSprite] != nullptr)
	{
		myObjectiveSprites[myCurrentObjectiveSprite]->Draw(myPosition+ CommonUtilities::Point2f(0,1));
	}

	/*if (CheckHasCandy() == true)
	{
		ourCandySprite->Draw(myPosition);
	}*/
}

void IsometricTile::Update()
{
	if (myNavVertex.Null() == false)
	{
		if (myNavVertex->IsSearched() == true)
		{
			myState = eTileState::IN_RANGE;
		}
		else
		{
			myState = eTileState::IS_WALKABLE;
		}
	}
}

void IsometricTile::SetShader(DX2D::CCustomShader* aCustomShader)
{
	for (size_t i = 0; i < myGraphicsLayers.Size(); i++)
	{
		myGraphicsLayers[i]->SetShader(aCustomShader);
	}

	if (myObjectiveSprites[0] != nullptr)
	{
		myObjectiveSprites[0]->SetShader(aCustomShader);
	}

	if (myObjectiveSprites[1] != nullptr)
	{
		myObjectiveSprites[1]->SetShader(aCustomShader);
	}
}

void IsometricTile::AddSpriteLayer(std::shared_ptr<StaticSprite> aSprite)
{
	aSprite->SetPivotWithPixels(CU::Vector2f(64.f, 32.f));
	myGraphicsLayers.Add(aSprite);
}

void IsometricTile::SetDoor(const Door& aDoor)
{
	myDoor = aDoor;
}

void IsometricTile::SetObjectiveSprites(const CommonUtilities::StaticArray<std::shared_ptr<StaticSprite>, 2> someSprites)
{
	myObjectiveSprites = someSprites;
}

void IsometricTile::SetVertexHandle(VertexHandle aHandle)
{
	myNavVertex = aHandle;
}

void IsometricTile::SetVisible(bool aIsVisible)
{
	myIsVisible = aIsVisible;
}

void IsometricTile::SetDiscovered(bool aIsDiscovered)
{
	myIsDiscovered = aIsDiscovered;
}

void IsometricTile::SetInEnemyFoV(bool aIsInFoV, const Enemy* aEnemy)
{
	myIsInEnemyFoV = aIsInFoV;
	myEnemy = aEnemy;
}

bool IsometricTile::GetVisible() const
{
	return myIsVisible;
}

bool IsometricTile::GetDiscovered() const
{
	return myIsDiscovered;
}

bool IsometricTile::GetInEnemyFov() const
{
	return myIsInEnemyFoV;
}

const Enemy* IsometricTile::GetSeenEnemy() const
{
	return myEnemy;
}

void IsometricTile::RemoveAvailableDirection(eDirection aDirection)
{
	myAvailableDirections.RemoveCyclic(aDirection);
}



VertexHandle IsometricTile::GetVertexHandle() const
{
	return myNavVertex;
}
