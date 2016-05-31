#pragma once
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Timer/Time.h>
#include <CU/Vectors/vector2.h>
#include <CU/Camera/Camera2D.h>
#include <GameObjects/Room/GameFloor.h>
#include <PostMaster/MessageReceiver.h>

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

	virtual void RecieveMessage(const PlayerObjectMessage & aMessage) override;
	virtual void RecieveMessage(const ActorPositionChangedMessage & aMessage) override;
	virtual void RecieveMessage(const PlayerAddedMessage & aMessage) override;

private:
	void RayTrace(const CU::Vector2f &aPosition, const CU::Vector2f &anotherPosition);
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
};

inline Player* PlayerController::GetSelectedPlayer()
{
	return mySelectedPlayer;
}
