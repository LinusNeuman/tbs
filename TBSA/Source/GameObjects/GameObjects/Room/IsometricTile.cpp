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
	myIsInEnemyFoV = false;
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

void IsometricTile::AddSpriteLayer(StaticSprite * aSprite)
{
	aSprite->SetPivotWithPixels(CU::Vector2f(64.f, 32.f));
	myGraphicsLayers.Add(aSprite);
}

void IsometricTile::SetDoor(const Door& aDoor)
{
	myDoor = aDoor;
}

void IsometricTile::SetVertexHandle(VertexHandle aHandle)
{
	myNavVertex = aHandle;
}

void IsometricTile::SetVisible(bool aIsVisible)
{
	myIsVisible = aIsVisible;
}

void IsometricTile::SetInEnemyFoV(bool aIsInFoV)
{
	myIsInEnemyFoV = aIsInFoV;
}

bool IsometricTile::GetVisible() const
{
	return myIsVisible;
}

bool IsometricTile::GetInEnemyFov() const
{
	return myIsInEnemyFoV;
}

VertexHandle IsometricTile::GetVertexHandle() const
{
	return myNavVertex;
}
