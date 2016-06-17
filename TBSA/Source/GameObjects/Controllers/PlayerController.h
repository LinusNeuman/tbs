#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Timer/Time.h>
#include <CU/Vectors/vector2.h>
#include <CU/Camera/Camera2D.h>
#include <GameObjects/Room/GameFloor.h>
#include <PostMaster/MessageReceiver.h>
#include <CU/Utility/GameSpecificTypeDefs.h>
#include <Input/LayeredInput/LayerInputReciever.h>
#include <Audio\Instances\SoundEffect.h>
#include "Controllers\ScoreCounter.h"
#include "Controllers\enumMouseState.h"
#include "Controllers\MouseController.h"

class PlayState;
class Actor;
class RenderConverter;
class Player;

class PlayerController : public MessageReciever
{
public:
	PlayerController();
	~PlayerController();

	void Init();
	void Draw() const;

	void AddPlayer(Player * aPlayer);
	void SelectPlayer();
	void NotifyPlayers(CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> aPath) const;
	Player* GetSelectedPlayer();
	int GetPlayerAP();
	void SuggestCostAP(const int anAP);
	void CostAP(const int anAP);
	void Update(const CommonUtilities::Time& aTime);
	void ConstantUpdate(const CommonUtilities::Time& aDeltaTime);

	void SetFloor(GameFloor & aFloor);
	void PrePlayer();
	void SetCameraPositionToPlayer(int aIndex);
	void AfterPlayerTurn();
	

	void PlayerSeen(CommonUtilities::Point2i aPlayerPosition, const Enemy* aEnemy);

	virtual bool RecieveMessage(const PlayerObjectMessage & aMessage) override;
	virtual bool RecieveMessage(const BaseMessage & aMessage) override;
	virtual bool RecieveMessage(const PlayerPositionChangedMessage & aMessage) override;
	virtual bool RecieveMessage(const PlayerAddedMessage & aMessage) override;
	virtual bool RecieveMessage(const EnemyPositionChangedMessage & aMessage) override;
	virtual bool RecieveMessage(const EnemyDirectionChangedMessage & aMessage) override;
	virtual bool RecieveMessage(const EnemyObjectMessage & aMessage) override;
	virtual bool RecieveMessage(const PlayerIDMessage & aMessage) override;
	virtual bool RecieveMessage(const GUIMessage & aMessage) override;
	virtual bool RecieveMessage(const TextMessage & aMessage) override;
	virtual bool RecieveMessage(const EnemyNextPathMessage & aMessage) override;
	virtual bool RecieveMessage(const PlayerDiedMessage & aMessage) override;

private:
	void AddCandy(const unsigned short aCandyAmount = 0);
	void EatCandy();
	bool CheckIfPlayerIsAllowedInput();

	int GetPlayerAttackAPCost() const;

	bool CheckForCandy(const TilePosition & aPosToCheckForCandyAt);
	void TakeCandy(const TilePosition & aPosToTakeCandyFrom);

	void ActivePlayerFight(const unsigned short aPlayerIndex);
	bool CheckIfCloseToDoor(const CU::Vector2ui &aPosition, const CU::Vector2ui &aOldPosition, CU::Vector2ui &aPeakLocation) const;

	void BuildPath(PathArray & aPathContainterToBuild);
	enumMouseState GetCurrentMouseState();

	void RayTrace(const TilePositionf &aPosition, const TilePositionf &anotherPosition);
	int CalculatePoint(float aValue) const;
	void ResetTileShaders();
	void CreatePlayerFoV(const CU::Vector2f& aPosition, float aRadius);
	void CalculateCircleRayTrace(const CU::Vector2f& aPosition, const CU::Vector2f& anotherPosition);

	GameFloor * myFloor;

	Camera2D myCamera;

	CommonUtilities::GrowingArray<Player*> myPlayers;
	CommonUtilities::Vector2f myMousePosition;
	Player *mySelectedPlayer;
	unsigned short mySelectedPlayerIndex;

	unsigned short myCandy;

	bool myPlayerTurnFlag;

	bool myFakeClickedOnEnemy;
	bool myClickedOnPlayer;
	bool myClickedOnEnemy;
	bool myClickedOnBB;
	bool myClickedOnSelectedPlayer;

	LayerInputReciever myMouseInput;

	std::vector<CU::Vector2f> myDebugStart;
	std::vector<CU::Vector2f> myDebugEnd;

	SoundEffect* mySelectPlayerSound;
	SoundEffect* myAlertSound;
	SoundEffect* myCandySound;
	SoundEffect* myPeekSound;

	SoundEffect* myWalkAcceptSound[4];

	ScoreCounter myScoreCounter;

	MouseController myMouseController;

};

inline Player* PlayerController::GetSelectedPlayer()
{
	return mySelectedPlayer;
}
