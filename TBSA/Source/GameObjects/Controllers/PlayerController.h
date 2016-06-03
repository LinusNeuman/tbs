#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Timer/Time.h>
#include <CU/Vectors/vector2.h>
#include <CU/Camera/Camera2D.h>
#include <GameObjects/Room/GameFloor.h>
#include <PostMaster/MessageReceiver.h>
#include <CU/Utility/GameSpecificTypeDefs.h>

class PlayState;
class Actor;
class RenderConverter;
class Player;

enum class enumMouseState
{
	eClickedOnEnemy,
	eClickedOnPlayer,
	eClickedOnEmptyTile,
	eClickedOnVoid,
	enumLength
};

class PlayerController : public MessageReciever
{
public:
	PlayerController();
	~PlayerController();

	void Init();

	void AddPlayer(Player * aPlayer);
	void SelectPlayer();
	void NotifyPlayers(CommonUtilities::GrowingArray<CommonUtilities::Vector2ui> aPath) const;
	Player* GetSelectedPlayer();
	int GetPlayerAP();
	void CostAP(const int anAP);
	void Update(const CommonUtilities::Time& aTime);
	void ConstantUpdate(const CommonUtilities::Time& aDeltaTime);

	void SetFloor(GameFloor & aFloor);
	void PrePlayer();
	void RefillAllAP();
	void SetCameraPositionToPlayer(int aIndex);
	void AfterPlayerTurn();

	void PlayerSeen(CommonUtilities::Point2i aPlayerPosition);

	virtual bool RecieveMessage(const PlayerObjectMessage & aMessage) override;
	virtual bool RecieveMessage(const PlayerPositionChangedMessage & aMessage) override;
	virtual bool RecieveMessage(const PlayerAddedMessage & aMessage) override;
	virtual bool RecieveMessage(const EnemyDirectionChangedMessage & aMessage) override;
	virtual bool RecieveMessage(const EnemyObjectMessage & aMessage) override;

private:
	void ActivePlayerFight(const unsigned short aPlayerIndex);
	bool CheckIfCloseToDoor(const CU::Vector2ui &aPosition, CU::Vector2ui &aPeakLocation) const;

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

	bool myClickedOnPlayer;
	bool myClickedOnEnemy;

	std::vector<CU::Vector2f> myDebugStart;
	std::vector<CU::Vector2f> myDebugEnd;

};

inline Player* PlayerController::GetSelectedPlayer()
{
	return mySelectedPlayer;
}
