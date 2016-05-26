// Author:   Hampus Huledal
// CreationDate: 26/05/2016
#pragma once
#include <GameObjects/Actor/Enemy.h>

class EnemyController
{
public:
	EnemyController();
	~EnemyController();
	void PreTurn();
	void Update(CommonUtilities::Time aDetltaTime);
	void ConstantUpdate(CommonUtilities::Time aDeltaTime);
	void Draw();

private:
	void EnemyDone();

	CommonUtilities::GrowingArray<Enemy> myEnemies;
	
	unsigned short myCurrentEnemy;
};
