﻿#include "stdafx.h"
#include "EnemyController.h"
#include "PostMaster/SingletonPostMaster.h"
#include <Message/EndTurnMessage.h>
#include <GameObjects/Room/IsometricTile.h>
#include <GameObjects/Room/GameFloor.h>
#include <Message/EnemyPositionChangedMessage.h>
#include <Message/FightWithEnemyMessage.h>
#include "../../GUI/GUI/Messaging/Generic/GUIMessage.h"


EnemyController::EnemyController()
{
	myEnemies.Init(1);
	myCurrentEnemy = 0;
}

EnemyController::~EnemyController()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eStartFight, *this);
}

void EnemyController::Init()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eStartFight, *this);
}

void EnemyController::PreTurn()
{
	myCurrentEnemy = 0;
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myEnemies[i]->Reset();
	}

	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myFloor->SetDiagonals(myEnemies[i]->GetPosition(), 1.1f);
	}
}

void EnemyController::Update(CommonUtilities::Time aDeltaTime)
{
	if (myEnemies.Size() > 0 && myCurrentEnemy < myEnemies.Size())
	{
		myEnemies[myCurrentEnemy]->UpdateEnemy();
	}
	else
	{
		SendPostMessage(GUIMessage(RecieverTypes::eEndTurn));
	}
}

void EnemyController::ConstantUpdate(CommonUtilities::Time aDeltaTime)
{
	ResetTileShaders();
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		if (myEnemies[i]->GetActiveState() == true)
		{
			CreateEnemyRayTrace(CU::Vector2f(myEnemies[i]->GetTargetPosition()), myEnemies[i]->GetDirectionEnum(), 45.f, 4.f);
			SendPostMessage(EnemyPositionChangedMessage(RecieverTypes::eEnemyPositionChanged));
		}
	}
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myEnemies[i]->Update(aDeltaTime);
		if(myFloor->GetTile(CU::Vector2ui(USHORTCAST(myEnemies[i]->GetPosition().x), USHORTCAST(myEnemies[i]->GetPosition().y))).GetVisible() == true)
		{
			myEnemies[i]->SetVisibleState(true);
		}
		else
		{
			myEnemies[i]->SetVisibleState(false);
		}
		
	}
	
}

void EnemyController::Draw()
{
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{		
		if (myEnemies[i]->GetVisibleState() == true)
		{
			myEnemies[i]->Draw();
		}
	}
}

void EnemyController::EnemyDone()
{
	++myCurrentEnemy;
	if (myCurrentEnemy >= myEnemies.Size())
	{
		SendPostMessage(GUIMessage(RecieverTypes::eEndTurn));
	}
	else
	{
		myEnemies[myCurrentEnemy]->Reset();
	}
}

void EnemyController::SetFloor(GameFloor& aFloor)
{
	myFloor = &aFloor;
}

void EnemyController::RayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition, eDirection aDirection)
{
	CU::Vector2f position = aPosition;
	CU::Vector2f secondPosition = anotherPosition;
	double x0, x1, y0, y1;
	x0 = position.x;
	y0 = position.y;
	x1 = secondPosition.x;
	y1 = secondPosition.y;
	int dx = abs(static_cast<int>(x1 - x0));
	int dy = abs(static_cast<int>(y1 - y0));
	int x = static_cast<int>(x0);
	int y = static_cast<int>(y0);
	int n = 1 + dx + dy;
	int x_inc = (x1 > x0) ? 1 : -1;
	int y_inc = (y1 > y0) ? 1 : -1;
	int error = dx - dy;
	dx *= 2;
	dy *= 2;

	for (; n > 0; --n)
	{
		if (myFloor->GetTile(x, y).GetTileType() == eTileType::BLOCKED || myFloor->GetTile(x, y).GetTileType() == eTileType::DOOR || myFloor->GetTile(x, y).GetTileType() == eTileType::COVER)
		{
			break;
		}
		for (unsigned int i = 0; i < myFloor->GetTile(x, y).GetAvailableDirections().Size(); i++)
		{
			if (myFloor->GetTile(x, y).GetAvailableDirections()[i] == aDirection)
			{
				myFloor->GetTile(x, y).SetInEnemyFoV(true);
				break;
			}
		}
		
		if (error > 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}
	

}

void EnemyController::CreateEnemyRayTrace(const CU::Vector2f &aPosition, eDirection aDirection, float aAngle, float aMagnitude)
{
	switch (aDirection)
	{
	case eDirection::NORTH:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(0.0f, -1.0f), aAngle, aMagnitude, aDirection);
		break;
	case eDirection::NORTH_EAST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(1.0f, -1.0f), aAngle, aMagnitude, aDirection);
		break;
	case eDirection::EAST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(1.0f, 0.0f), aAngle, aMagnitude, aDirection);
		break;
	case eDirection::SOUTH_EAST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(1.0f, 1.0f), aAngle, aMagnitude, aDirection);
		break;
	case eDirection::SOUTH:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(0.0f, 1.0f), aAngle, aMagnitude, aDirection);
		break;
	case eDirection::SOUTH_WEST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(-1.0f, 1.0f), aAngle, aMagnitude, aDirection);
		break;
	case eDirection::WEST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(-1.0f, 0.0f), aAngle, aMagnitude, aDirection);
		break;
	case eDirection::NORTH_WEST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(-1.0f, -1.0f), aAngle, aMagnitude, aDirection);
		break;
	default:
		break;
	}
	
	
}

void EnemyController::CalculateFoVBasedOnAngle(const CU::Vector2f& aPosition, const CU::Vector2f &aShouldBeEnemyDirection, float aAngleInDegrees, float aMagnitude, eDirection aDirection)
{
	float angle = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() - abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 2.f)));
	float angle2 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() + abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 2.f)));
	float angle3 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() - abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 4.f)));
	float angle4 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() + abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 4.f)));
	float angle5 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle());
	CU::Vector2f test = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle))));
	CU::Vector2f test3 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle3))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle3))));
	CU::Vector2f test2 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle2))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle2))));
	CU::Vector2f test4 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle4))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle4))));

	CU::Vector2f test5;

	if (aShouldBeEnemyDirection.x == 0 && aShouldBeEnemyDirection.y == 1)
	{
		test5 = CU::Vector2f(ceil(aMagnitude * cos(angle5)), ceil(aMagnitude * sin(angle5)));
	}
	else if (aShouldBeEnemyDirection.x == 1 && aShouldBeEnemyDirection.y == 0)
	{
		test5 = CU::Vector2f(ceil(aMagnitude * cos(angle5)), floor(aMagnitude * sin(angle5)));
	}
	else if (aShouldBeEnemyDirection.x == 0 && aShouldBeEnemyDirection.y == -1)
	{
		test5 = CU::Vector2f(floor(aMagnitude * cos(angle5)), ceil(aMagnitude * sin(angle5)));
	}
	else
	{
		test5 = CU::Vector2f(floor(aMagnitude * cos(angle5)), floor(aMagnitude * sin(angle5)));
	}

	RayTrace(aPosition, aPosition + test, aDirection);
	RayTrace(aPosition, aPosition + test2, aDirection);
	RayTrace(aPosition, aPosition + test3, aDirection);
	RayTrace(aPosition, aPosition + test4, aDirection);
	RayTrace(aPosition, aPosition + test5, aDirection);
}

int EnemyController::CalculatePoint(float aValue) const
{
	if (aValue <= 0)
	{
		return static_cast<int>(floor(aValue));
	}
	return static_cast<int>(ceil(aValue));
}

void EnemyController::ResetTileShaders()
{
	for (unsigned int i = 0; i < myFloor->Size(); i++)
	{
		myFloor->GetTile(i).SetInEnemyFoV(false);
	}
}

void EnemyController::AddEnemy(Enemy* aEnemy)
{
	aEnemy->myController = this;
	myEnemies.Add(aEnemy);
	myEnemies.GetLast()->SetIndex(myEnemies.Size() - 1);
}

bool EnemyController::RecieveMessage(const FightWithEnemyMessage & aMessage)
{
	myEnemies[aMessage.myEnemyIndex]->Fight();
	return true;
}

void EnemyController::PostTurn()
{
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myFloor->SetDiagonals(myEnemies[i]->GetPosition(), 10000 * 10000);
		myEnemies[i]->AfterTurn();
	}
}

