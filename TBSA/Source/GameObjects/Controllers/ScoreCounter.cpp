#include "stdafx.h"
#include "ScoreCounter.h"


ScoreCounter::ScoreCounter()
{
	myScoreArray.Init(USHORTCAST(enumScoreTypes::enumLenght));
	myScoreArray.Resize(USHORTCAST(enumScoreTypes::enumLenght));

	for (unsigned short iScore = 0; iScore < myScoreArray.Size(); ++iScore)
	{
		myScoreArray[iScore] = 0;
	}
}


ScoreCounter::~ScoreCounter()
{
}
