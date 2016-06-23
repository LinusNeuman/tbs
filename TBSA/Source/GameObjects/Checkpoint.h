#pragma once

struct CheckpointData
{
	CheckpointData()
	{
		myRespawnPosition = CU::Vector2ui(UINT_MAX, UINT_MAX);
		mySavedDeadEnemies.Init(10);
	}
	CommonUtilities::GrowingArray<SavedDeadEnemy> mySavedDeadEnemies;
	TilePosition myRespawnPosition;
	ObjectiveManager myObjectiveState; //Denna kommer att krasha spelet d� den kommer f� massor av meddelanden och kommer f�rs�ka g�ra saker med dom utan att vara initade.
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
