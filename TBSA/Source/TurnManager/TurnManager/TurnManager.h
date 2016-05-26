// Author:   Hampus Huledal
// CreationDate: 26/05/2016
#pragma once
#include <PostMaster/MessageReceiver.h>
#include <Controllers/PlayerController.h>
#include <CU/Timer/Time.h>
#include <Controllers/EnemyController.h>

enum class eTurn
{
	//the turns will come in the order below!

	PRE_PLAYER_TURN,
	PLAYER_TURN,
	PLAYER_END_TURN,
	PRE_ENEMY_TURN,
	ENEMY_TURN,
	
	Size
};

class TurnManager : public MessageReciever
{
public:
	TurnManager();
	~TurnManager();

	void Update(CommonUtilities::Time aDeltaTime);

	PlayerController & GetPlayerController();

	EnemyController & GetEnemyController();

	void ForceTurn(eTurn aTurn);
private:
	void EndTurn();

	void PreparePlayer();
	void UpdatePlayer(CommonUtilities::Time aDeltaTime);
	void PlayerEndTurn();
	
	void PrepareEnemy();
	void UpdateEnemy(CommonUtilities::Time aDeltaTime);

	eTurn myCurrentTurn;

	PlayerController myPlayerController;
	EnemyController myEnemyController;
};

inline PlayerController& TurnManager::GetPlayerController()
{
	return myPlayerController;
}


inline EnemyController& TurnManager::GetEnemyController()
{
	return myEnemyController;
}
