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
	eEndTurn,
	eStartUpLevel,
	eExitGame,
	eMouseClicked,
	eChangeSelectedPlayer,
	eClickedOnPlayer,
	ePlayGame,
	ePlayerPositionChanged,
	eEnemyPositionChanged,
	ePlayerAdded,
	eWindowHandleChange,
	ePlayerChangedTarget,
	ePlayEvents,
	eClickedOnEnemy,
	ePlayerReachedEndOfPath,
	eEnemyReachedEndOfPath,
	ePlayerNextToObjective,
	ePlayerTargetEnemy,
	ePlayerAPChanged,
	eStartFight,
	eFlagPlayerDied,
	eEnemyAttacked,
	eGoalReached,
	eFlagGoalReached,
	ePlayerCanPeek,
	eMouseInput,
	eOpenPauseMenu,
	eGameOverReset,
	eClosePauseMenu,
	enumlength
};