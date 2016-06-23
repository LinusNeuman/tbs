#pragma once
#include "Controllers\ScoreCounter.h"



struct CheckpointData
{
	CheckpointData()
	{
		myRespawnPosition = CU::Vector2ui(UINT_MAX, UINT_MAX);
		mySavedDeadEnemies.Init(10);
	}
	CommonUtilities::GrowingArray<SavedDeadEnemy> mySavedDeadEnemies;
	TilePosition myRespawnPosition;
	ObjectiveManager myObjectiveState;
	ScoreCounter myScoreCounter;
};


class Checkpoint
{
public:
	Checkpoint()
	{

	}
	~Checkpoint()
	{

	}

	void SetPosition(const CommonUtilities::Vector2f & aPos)
	{
		myPosition = aPos;
	}

	CU::Vector2f GetPosition() const
	{
		return myPosition;
	}

private:

	CU::Vector2f myPosition;
	bool myIsActivated;
};
