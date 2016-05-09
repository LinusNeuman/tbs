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

void PlayerController::SelectPlayer()
{
	for (unsigned short i = 0; i < myPlayers.Size(); i++)
	{
		myPlayers[i]->SetSelected(!myPlayers[i]->GetIsSelected());
	}
}

void PlayerController::NotifyPlayers(const CU::Time aDeltaTime)
{
	for (unsigned short i = 0; i < myPlayers.Size(); i++)
	{
		if (myPlayers[i] != nullptr && myPlayers[i]->GetIsSelected() == true)
		{
			myPlayers[i]->Move(GetInput::GetMouseWindowPosition() /64.f, aDeltaTime);
		}
	}
}