#include "stdafx.h"
#include "GameObjectCollider.h"
//#include <Intersection/Intersection2D.h>
//#include <Renderer.h>
//#include <DebugLineRenderCommand.h>
//#include <Isometric/IsometricConversion.h>
////#include "tga2d/drawers/line_drawer.h"
//
//#include "tga2d\engine.h"
//#include "tga2d\drawers\debug_drawer.h"
//#include <Isometric\IsometricConversion.h>



GameObjectCollider::GameObjectCollider()
{
}


GameObjectCollider::~GameObjectCollider()
{
}

bool GameObjectCollider::CheckCollision(const GameObjectCollider & aCircleToTestCollisionWith) const
{
	return false;
}

void GameObjectCollider::DrawCollider(const CU::Vector4f & aRenderColor) const
{
	
}

bool GameObjectCollider::CheckCollisionAgainstCircle(const CircleCollider & aColliderToCheckAgainst) const
{
	return false;
}

bool GameObjectCollider::CheckCollisionAgainstBox(const BoxCollider & aColliderToCheckAgainst) const
{
	return false;
}

bool GameObjectCollider::CheckCollisionAgainstPoint(const PointCollider & aColliderToCheckAgainst) const
{
	return false;
}
