#include "stdafx.h"
#include "EnemyController.h"
#include "PostMaster/SingletonPostMaster.h"
#include <Message/EndTurnMessage.h>
#include <GameObjects/Room/IsometricTile.h>
#include <GameObjects/Room/GameFloor.h>
#include <Message/EnemyPositionChangedMessage.h>
#include <Message/FightWithEnemyMessage.h>
#include "../../GUI/GUI/Messaging/Generic/GUIMessage.h"
#include <Message/EnemyObjectMessage.h>
#include <Rend/RenderConverter.h>


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
	myDebugStart.clear();
	myDebugEnd.clear();
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		if (myEnemies[i]->GetActorState() != eActorState::eDead && myEnemies[i]->GetActorState() != eActorState::eFighting)
		{	
			CreateEnemyRayTrace(CU::Vector2f(myEnemies[i]->GetTargetPosition()), myEnemies[i]->GetDirectionEnum(), 45.f, myEnemies[i]->GetViewDistance(), myEnemies[i]);
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
	/*for (size_t i = 0; i < myDebugEnd.size(); i++)
	{
	DRAWISOMETRICLINE(myDebugStart[i], myDebugEnd[i]);
	}*/
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

void EnemyController::RayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition, eDirection aDirection, Enemy *aEnemy)
{
	CU::Vector2f position = aPosition;
	CU::Vector2f secondPosition = anotherPosition;
	double x0, x1, y0, y1;
	x0 = position.x;
	y0 = position.y;
	x1 = secondPosition.x;
	y1 = secondPosition.y;

	myDebugStart.push_back(position);
	myDebugEnd.push_back(secondPosition);

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
				if (aEnemy->GetType() == eActorType::eEnemyThree)
				{
					if (n > 2)
					{
						continue;
					}
				}
				myFloor->GetTile(x, y).SetInEnemyFoV(true, aEnemy);
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

void EnemyController::CreateEnemyRayTrace(const CU::Vector2f &aPosition, eDirection aDirection, float aAngle, float aMagnitude, Enemy *aEnemy)
{
	switch (aDirection)
	{
	case eDirection::NORTH:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(0.0f, -1.0f), aAngle, aMagnitude, aDirection, aEnemy, (aMagnitude/2));
		break;
	case eDirection::NORTH_EAST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(1.0f, -1.0f), aAngle, aMagnitude, aDirection, aEnemy, (aMagnitude / 2) + 1);
		break;
	case eDirection::EAST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(1.0f, 0.0f), aAngle, aMagnitude, aDirection, aEnemy, (aMagnitude / 2) + 1);
		break;
	case eDirection::SOUTH_EAST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(1.0f, 1.0f), aAngle, aMagnitude, aDirection, aEnemy, (aMagnitude / 2) + 1);
		break;
	case eDirection::SOUTH:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(0.0f, 1.0f), aAngle, aMagnitude, aDirection, aEnemy, (aMagnitude / 2) + 1);
		break;
	case eDirection::SOUTH_WEST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(-1.0f, 1.0f), aAngle, aMagnitude, aDirection, aEnemy, (aMagnitude / 2) + 1);
		break;
	case eDirection::WEST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(-1.0f, 0.0f), aAngle, aMagnitude, aDirection, aEnemy, (aMagnitude / 2) + 1);
		break;
	case eDirection::NORTH_WEST:
		CalculateFoVBasedOnAngle(aPosition, CU::Vector2f(-1.0f, -1.0f), aAngle, aMagnitude, aDirection, aEnemy, (aMagnitude / 2) + 1);
		break;
	default:
		break;
	}
	
	
}

void EnemyController::CalculateFoVBasedOnAngle(const CU::Vector2f& aPosition, const CU::Vector2f &aShouldBeEnemyDirection, float aAngleInDegrees, float aMagnitude, eDirection aDirection, Enemy *aEnemy, int aNumberOfIterations)
{
	/*if (aNumberOfIterations == 0)
		return;
	float angle;
	CU::Vector2f vector;
	if (aAngleInDegrees == 45.f)
	{
		angle = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle());
		if (aShouldBeEnemyDirection.x == 0 && aShouldBeEnemyDirection.y == 1)
			vector = CU::Vector2f(ceil(aMagnitude * cos(angle)), ceil(aMagnitude * sin(angle)));
		else if (aShouldBeEnemyDirection.x == 1 && aShouldBeEnemyDirection.y == 0)
			vector = CU::Vector2f(ceil(aMagnitude * cos(angle)), floor(aMagnitude * sin(angle)));
		else if (aShouldBeEnemyDirection.x == 0 && aShouldBeEnemyDirection.y == -1)
			vector = CU::Vector2f(floor(aMagnitude * cos(angle)), ceil(aMagnitude * sin(angle)));
		else
			vector = CU::Vector2f(floor(aMagnitude * cos(angle)), floor(aMagnitude * sin(angle)));
	}
	else
	{
		if (aAngleInDegrees > 0)
			angle = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() + abs(DEGRESS_TO_RADIANSF(aAngleInDegrees)));
		else
			angle = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() - abs(DEGRESS_TO_RADIANSF(aAngleInDegrees)));
		vector = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle))));
	}
	for (size_t i = 0; i < 2; i++)
	{
		if (i == 0)
			CalculateFoVBasedOnAngle(aPosition, aShouldBeEnemyDirection, aAngleInDegrees / 2.f, aMagnitude, aDirection, aNumberOfIterations - 1);
		else
			CalculateFoVBasedOnAngle(aPosition, aShouldBeEnemyDirection, -(aAngleInDegrees / 2.f), aMagnitude, aDirection, aNumberOfIterations - 1);
	}
	RayTrace(aPosition, aPosition + vector, aDirection);*/


	float angle = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() - abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 2.f)));
	float angle2 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() + abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 2.f)));
	float angle3 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() - abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 4.f)));
	float angle4 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() + abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 4.f)));
	float angle6 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() - abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 6.f)));
	float angle7 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle() + abs(DEGRESS_TO_RADIANSF(aAngleInDegrees / 6.f)));
	float angle5 = abs((aPosition - aPosition + aShouldBeEnemyDirection).GetAngle());
	CU::Vector2f vector = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle))));
	CU::Vector2f vector3 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle3))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle3))));
	CU::Vector2f vector2 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle2))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle2))));
	CU::Vector2f vector4 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle4))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle4))));
	CU::Vector2f vector6 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle6))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle6))));
	CU::Vector2f vector7 = CU::Vector2f(static_cast<float>(CalculatePoint(aMagnitude * cos(angle7))), static_cast<float>(CalculatePoint(aMagnitude * sin(angle7))));
	CU::Vector2f vector5;

	if (aShouldBeEnemyDirection.x == 0 && aShouldBeEnemyDirection.y == 1)
	{
		vector5 = CU::Vector2f(ceil(aMagnitude * cos(angle5)), ceil(aMagnitude * sin(angle5)));
	}
	else if (aShouldBeEnemyDirection.x == 1 && aShouldBeEnemyDirection.y == 0)
	{
		vector5 = CU::Vector2f(ceil(aMagnitude * cos(angle5)), floor(aMagnitude * sin(angle5)));
	}
	else if (aShouldBeEnemyDirection.x == 0 && aShouldBeEnemyDirection.y == -1)
	{
		vector5 = CU::Vector2f(floor(aMagnitude * cos(angle5)), ceil(aMagnitude * sin(angle5)));
	}
	else
	{
		vector5 = CU::Vector2f(floor(aMagnitude * cos(angle5)), floor(aMagnitude * sin(angle5)));
	}

	RayTrace(aPosition, aPosition + vector, aDirection, aEnemy);
	RayTrace(aPosition, aPosition + vector2, aDirection, aEnemy);
	RayTrace(aPosition, aPosition + vector3, aDirection, aEnemy);
	RayTrace(aPosition, aPosition + vector4, aDirection, aEnemy);
	RayTrace(aPosition, aPosition + vector5, aDirection, aEnemy);
	RayTrace(aPosition, aPosition + vector6, aDirection, aEnemy);
	RayTrace(aPosition, aPosition + vector7, aDirection, aEnemy);
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
		myFloor->GetTile(i).SetInEnemyFoV(false, nullptr);
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
		myEnemies[i]->AfterTurn();
	}
}

