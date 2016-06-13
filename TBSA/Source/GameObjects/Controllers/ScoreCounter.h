#pragma once
#include "Controllers/ScoreTypes.h"

typedef float ScoreType;


class ScoreCounter
{
public:
	ScoreCounter();
	~ScoreCounter();

	void AddScore(const enumScoreTypes aScoreTypeToIncrease, const ScoreType aValueToIncreaseWith);
	ScoreType GetScore(const enumScoreTypes aScoreTypeToGet) const;

private:
	CU::GrowingArray<ScoreType> myScoreArray;
};

inline void ScoreCounter::AddScore(const enumScoreTypes aScoreTypeToIncrease, const ScoreType aValueToIncreaseWith)
{
	DL_ASSERT(aValueToIncreaseWith > static_cast<ScoreType>(0), "Trying too increase score with a negative value!");
	myScoreArray[USHORTCAST(aScoreTypeToIncrease)] += aValueToIncreaseWith;
}

inline ScoreType ScoreCounter::GetScore(const enumScoreTypes aScoreTypeToGet) const
{
	return myScoreArray[USHORTCAST(aScoreTypeToGet)];
}