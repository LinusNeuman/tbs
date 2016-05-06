#include "stdafx.h"
#include "PlayerController.h"
#include "Player/Player.h"


PlayerController::PlayerController()
{
	myPlayers.Init(2);
}


PlayerController::~PlayerController()
{
}

void PlayerController::AddPlayer(Player* aPlayer)
{
	myPlayers.Add(aPlayer);
}


void PlayerController::NotifyPlayers(const CU::Time aDeltaTime)
{
	for (size_t i = 0; i < myPlayers.Size(); i++)
	{
		if (myPlayers[i] != nullptr)
		{
			myPlayers[i]->Move(GetInput::GetMouseWindowPosition() /64.f, aDeltaTime);
		}
	}
}
