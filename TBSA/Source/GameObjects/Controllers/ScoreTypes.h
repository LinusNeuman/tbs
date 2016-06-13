#pragma once

enum class enumScoreTypes
{
	eTurnCount,
	eEnemiesKilled,
	eCandy,
	enumLenght
};

#define SCORECAST(variable) static_cast<enumScoreTypes>((variable))