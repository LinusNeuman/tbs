#pragma once 

enum class eActorType
{
	ePlayerOne,
	ePlayerTwo,
	eEnemyOne,
	eEnemyTwo,
	eEnemyThree,
	eEnemyFour,
	eEnemyFive
};

enum class eDirection
{
	NORTH = 50,
	NORTH_EAST = 40,
	EAST = 30,
	SOUTH_EAST = 20,
	SOUTH = 10,
	SOUTH_WEST = 80,
	WEST = 70,
	NORTH_WEST = 60
};

enum class eActorState
{
	eIdle,
	eFighting,
	eDead,
	eWalking
};