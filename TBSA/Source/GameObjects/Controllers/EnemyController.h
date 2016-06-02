// Author:   Hampus Huledal
// CreationDate: 26/05/2016
#pragma once
#include <GameObjects/Actor/Enemy.h>
#include <PostMaster/MessageReceiver.h>


class GameFloor;

class EnemyController : public MessageReciever
{
public:
	EnemyController();
	~EnemyController();

	void Init();
	void PreTurn();
	void Update(CommonUtilities::Time aDeltaTime);
	void ConstantUpdate(CommonUtilities::Time aDeltaTime);
	void Draw();
	void EnemyDone();
	void SetFloor(GameFloor & aFloor);
	void AddEnemy(Enemy* aEnemy);

	virtual void RecieveMessage(const FightWithEnemyMessage & aMessage) override;
	void PostTurn();
private:
	void RayTrace(const CU::Vector2f &aPosition, const CU::Vector2f &anotherPosition);
	void CreateEnemyRayTrace(const CU::Vector2f &aPosition, const CU::Vector2f &aDirection, float aAngle, float aMagnitude);
	void CalculateFoVBasedOnAngle(const CU::Vector2f& aPosition, const CU::Vector2f& aShouldBeEnemyDirection, float aAngleInDegrees, float aMagnitude);
	int CalculatePoint(float aValue) const;
	void ResetTileShaders();

	CommonUtilities::GrowingArray<Enemy*> myEnemies;
	GameFloor * myFloor;

	unsigned short myCurrentEnemy;
};
