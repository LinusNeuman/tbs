#include "stdafx.h"
#include "GameFloor.h"
#include <CU/GrowingArray/GrowingArray.h>
#include <NavGraph/Vertex/NavVertex.h>

GameFloor::GameFloor()
{
}


GameFloor::~GameFloor()
{
}

void GameFloor::Update()
{
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Update));
}

void GameFloor::Draw() const
{
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&IsometricTile::Draw));
}

void GameFloor::Init(const unsigned short aSize)
{
	myTiles.Init(aSize);
}

void GameFloor::SetTiles(const TileArray & aTileArray)
{
	myTiles = aTileArray;
}

unsigned short GameFloor::Size() const
{
	return myTiles.Size();
}

void GameFloor::SetDiagonals(const CU::Vector2f& aPosition, float aCost)
{
	const IsometricTile tile = GetTile(CommonUtilities::Vector2ui(aPosition));
	VertexHandle vertex = tile.GetVertexHandle();
	DL_ASSERT(vertex.Null(), "something is off in set diagonals function, nav handle became null")
	CommonUtilities::GrowingArray<EdgeHandle> someEdges = vertex->GetEdges();

	for (size_t i = 0; i < someEdges.Size(); i++)
	{
		const int tileIndex = someEdges[i]->GoThrough(vertex)->GetAnyPurpouseId();
		const CommonUtilities::Vector2ui tilePosition(tileIndex % myDimensions.x, tileIndex / myDimensions.y);
		if (tilePosition.x == tile.GetPosition().x || tilePosition.y == tile.GetPosition().y)
		{
			continue;
		}

		someEdges[i]->Setcost(aCost);
	}
}
