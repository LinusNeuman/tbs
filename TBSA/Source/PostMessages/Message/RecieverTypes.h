#pragma once

enum class RecieverOrder
{
	eGUI,
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
	eTargetResolutionSet,
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
	eLogText,
	eClearLog,
	eScrollLogUp,
	eScrollLogDown,
	enumlength
};