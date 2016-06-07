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
	eStartFight,
	eFlagPlayerDied,
	eEnemyAttacked,
	eGoalReached,
	eFlagGoalReached,
	ePlayerCanPeek,
	eMouseInput,
	eOpenPauseMenu,
	eGameOverReset,
	enumlength
};