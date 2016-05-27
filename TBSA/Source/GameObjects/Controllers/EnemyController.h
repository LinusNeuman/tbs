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
	void Draw();
	void EnemyDone();
	void AddEnemy(Enemy* aEnemy);
private:
	

	CommonUtilities::GrowingArray<Enemy*> myEnemies;
	
	unsigned short myCurrentEnemy;
};
