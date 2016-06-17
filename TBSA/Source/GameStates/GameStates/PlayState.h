#pragma once
#include <StateStack/GameState.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/StaticArray/StaticArray.h>
#include <Message\ScoreCounterMessage.h>
#include <unordered_map>
#include <map>
#include <queue>
#include "../TextBox/TextBox.h"
#include "particleEmitter.h"
#include "Audio\Instances\Song.h"
#include <Controllers\ScoreCounter.h>
#include "Audio\Instances\SoundEffect.h"
#include <TiledData/TiledData.h>

class LevelFactory;
class GameLevel;
struct SavedDeadEnemy;

class PlayState : public GameState, public MessageReciever
{
public:
	PlayState();
	~PlayState();
	void Init(const std::string& aLevelPath = "");
	eStackReturnValue Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack) override;
	void Draw() const override;

	void ChangeLevel(const std::string& aFilePath);

	virtual bool RecieveMessage(const GoalReachedMessage& aMessage) override;
	virtual bool RecieveMessage(const PlayerDiedMessage & aMessage) override;
	virtual bool RecieveMessage(const StartUpLevelMessage & aMessage) override;
	virtual bool RecieveMessage(const GUIMessage & aMessage) override;
	virtual bool RecieveMessage(const TextMessage & aMessage) override;
	virtual bool RecieveMessage(const CheckpointMessage & aMessage) override;
	virtual bool RecieveMessage(const ScoreCounterMessage& aMessage);
	virtual bool RecieveMessage(const DeadEnemyMessage & aMessage) override;

private:
	ScoreCounter myScoreCounter;
	ParticleEmitter<250> myEmitter;
	GameLevel * myLevel;
	std::string myLevelKey;
	std::string myCurrentLevelpath;
	LevelFactory* myLevelFactory;
	SoundEffect* myAmbiance;
	Song* myMusic;
	TilePosition myRespawnPosition;
	CommonUtilities::GrowingArray<Enemy*> myDeadEnemies;
	const SavedDeadEnemy *myDeadEnemyData;
	bool scoreScreenDone;
	bool myShouldExit;
	bool myGameOver;
	bool myShouldPause;
	bool myShowPostLevelScreen;
	bool myFinishedGame;
	bool myHasTriggeredCheckpoint;
	

};
