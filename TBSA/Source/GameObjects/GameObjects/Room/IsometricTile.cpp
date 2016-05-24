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
}

IsometricTile::~IsometricTile()
{
}

void IsometricTile::Init()
{
	mySprite = new StaticSprite();
	mySprite->Init();
}

void IsometricTile::Draw() const
{
	CommonUtilities::Vector4f currentColour = CommonUtilities::Vector4f(1, 1, 1, 1);;

	switch (myType)
	{
	case eTileType::EMPTY: 
		currentColour = CommonUtilities::Vector4f(1, 1, 1, .5);
		break;
	case eTileType::OPEN: 
		currentColour = CommonUtilities::Vector4f(0, 1, 0, 1);
		break;
	case eTileType::BLOCKED:
		currentColour = CommonUtilities::Vector4f(1, 0, 0, 1);
		break;
	case eTileType::DOOR:
		currentColour = CommonUtilities::Vector4f(1, .7, 0, 1);
		break;
	case eTileType::DOOR_2: 
		currentColour = CommonUtilities::Vector4f(1, .9, 0, 1);
		break;
	case eTileType::Size: break;
	default: break;
	}

	switch (myState)
	{
	case eTileState::IN_RANGE:
	currentColour = CommonUtilities::Vector4f(0, 0, 1, 1);
	break;
	case eTileState::IN_PATH:
	currentColour = CommonUtilities::Vector4f(1, 1, 0, 1);
	break;
	case eTileState::IS_WALKABLE:
	case eTileState::NONE:
	case eTileState::Size:
	default:
	break;
	}

	for (USHORT i = 0; i < myGraphicsLayers.Size(); i++)
	{
		myGraphicsLayers[i]->SetColor(currentColour);
		myGraphicsLayers[i]->Draw(myPosition );
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

VertexHandle IsometricTile::GetVertexHandle() const
{
	return myNavVertex;
}
