﻿// Author:   Hampus Huledal
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
	ENEMY_END_TURN,
	Size
};

class TurnManager : public MessageReciever
{
public:
	TurnManager();
	~TurnManager();

	bool Update(CommonUtilities::Time aDeltaTime);

	PlayerController & GetPlayerController();

	EnemyController & GetEnemyController();

	void ForceTurn(eTurn aTurn);
	void RecieveMessage(const GUIMessage&) override;
	void RecieveMessage(const FlagPlayerDiedMessage&) override;
	void RecieveMessage(const FlagGoalReachedMessage&) override;
private:
	void EndTurn();

	bool PreparePlayer();
	bool UpdatePlayer(CommonUtilities::Time aDeltaTime);
	bool PlayerEndTurn();
	
	bool PrepareEnemy();
	bool UpdateEnemy(CommonUtilities::Time aDeltaTime);
	bool EnemyEndTurn();

	eTurn myCurrentTurn;
	bool myPlayerDied;
	bool myReachedGoal;
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
