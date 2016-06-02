#pragma once

enum class RecieverOrder
{
	eDefault = 100,
	enumLength
};

enum class RecieverTypes
{
	eRoom,
	eWindowProperties,
	ePlayer,
	eLevelTileLayoutSettings,
	eCamera,
	eTurn,
	eStartUpLevel,
	eEndTurn,
	eExitGame,
	eMouseClicked,
	eChangeSelectedPlayer,
	ePlayGame,
	eActorPositionChanged,
	ePlayerAdded,
	eEnemyDirectionChanged,
	eWindowHandleChange,
	ePlayerChangedTarget,
	ePlayEvents,
	eClickedOnEnemy,
	ePlayerReachedEndOfPath,
	eEnemyReachedEndOfPath,
	ePlayerNextToObjective,
	ePlayerTargetEnemy,
	eStartFight,
	eFlagPlayerDied,
	eEnemyAttacked,
	eGoalReached,
	eFlagGoalReached,
	enumlength
};