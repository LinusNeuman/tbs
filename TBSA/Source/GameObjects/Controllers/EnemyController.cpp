#include "stdafx.h"
#include "EnemyController.h"
#include "PostMaster/SingletonPostMaster.h"
#include <Message/EndTurnMessage.h>
#include <GameObjects/Room/IsometricTile.h>
#include <GameObjects/Room/GameFloor.h>
#include <Message/EnemyChangedDirectionMessage.h>
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
		myFloor->SetDiagonals(myEnemies[i]->GetPosition(), 1.1);
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
		SendPostMessage(GUIMessage(RecieverTypes::eTurn));
	}
}

void EnemyController::ConstantUpdate(CommonUtilities::Time aDeltaTime)
{
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myEnemies[i]->Update(aDeltaTime);
		if(myFloor->GetTile(CU::Vector2ui(myEnemies[i]->GetPosition().x, myEnemies[i]->GetPosition().y)).GetVisible() == true)
		{
			myEnemies[i]->SetVisibleState(true);
		}
		else
		{
			myEnemies[i]->SetVisibleState(false);
		}
		if (myEnemies[i]->GetActiveState() == true)
		{
			CreateEnemyRayTrace(CU::Vector2f(myEnemies[i]->GetTargetPosition()), myEnemies[i]->GetDirection(), 45.f, 4.f);
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
		SendPostMessage(GUIMessage(RecieverTypes::eTurn));
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

void EnemyController::RayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition)
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
		if (myFloor->GetTile(x, y).GetTileType() == eTileType::BLOCKED)
		{
			break;
		}
		myFloor->GetTile(x, y).SetInEnemyFoV(true);
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

void EnemyController::CreateEnemyRayTrace(const CU::Vector2f &aPosition, const CU::Vector2f &aDirection, float aAngle, float aMagnitude)
{
	ResetTileShaders();
	CalculateFoVBasedOnAngle(aPosition, aDirection, aAngle, aMagnitude);
	SendPostMessage(EnemyChangedDirectionMessage(RecieverTypes::eEnemyChangedDirection));
}

void EnemyController::CalculateFoVBasedOnAngle(const CU::Vector2f& aPosition, const CU::Vector2f &aShouldBeEnemyDirection, float aAngleInDegrees, float aMagnitude)
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
	//this should be alot less messy when enemies has directions, which would probably be with enums or something.

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

	RayTrace(aPosition, aPosition + test);
	RayTrace(aPosition, aPosition + test2);
	RayTrace(aPosition, aPosition + test3);
	RayTrace(aPosition, aPosition + test4);
	RayTrace(aPosition, aPosition + test5);
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

void EnemyController::RecieveMessage(const FightWithEnemyMessage & aMessage)
{
	myEnemies[aMessage.myEnemyIndex]->Fight();
}

void EnemyController::PostTurn()
{
	for (size_t i = 0; i < myEnemies.Size(); i++)
	{
		myFloor->SetDiagonals(myEnemies[i]->GetPosition(), 10000 * 10000);
	}
}
