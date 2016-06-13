#include "stdafx.h"
#include "APBox.h"
#include <Rend/RenderConverter.h>
#include <Rend/RenderCommand.h>
#include <CU/Matriser/matrix.h>

APBox::APBox()
{
	myAPText = new DX2D::CText("Text/calibril.ttf_sdf");
	mySprite = new StaticSprite();
	mySprite->Init("Sprites/GUI/HUD/AP/ActorAP.dds", true, CU::Vector4f::Zero, { 0.5f, 0.5f });
	mySprite->SetLayer(enumRenderLayer::eGUI);
	mySprite->SetPivotWithPixels({ mySprite->GetSizeInPixels().x / 2.f, -(mySprite->GetSizeInPixels().y / 2.f) });

	myEasing = 0.f;
	myMovementTimer = 0.f;
	myMovementTotalDown = 0.5f;
	myMovementTotalUp = 0.5f;

	myApBoxState = eAPBoxState::eGoingUp;
}

APBox::~APBox()
{
	//SAFE_DELETE(myAPText);
	//SAFE_DELETE(mySprite);
}

void APBox::Update()
{

}

void APBox::CalculateProgress(const CommonUtilities::Time aTime)
{
	myMovementTimer = myMovementTimer + aTime.GetSeconds();
	float progress = 0.f;
	if (myApBoxState == eAPBoxState::eGoingUp)
	{
		progress = myMovementTimer / myMovementTotalUp;
	}
	else
	{
		progress = myMovementTimer / myMovementTotalDown;
	}
	progress = TweenSine(progress);
	myEasing = progress;
}

void APBox::MoveUp(const CommonUtilities::Time aTime)
{
	myOriginalPosition = myTilePositionf;
	myGoalPosition = myTilePositionf;
	myGoalPosition.x = myTilePositionf.x + 0.1f;
	
	CU::Vector2f deltaPos = 
	{
		myPosition.x - myGoalPosition.x,
		myPosition.y - myGoalPosition.y
	};

	float hypotenusa = sqrt(pow(deltaPos.y, 2));
	CU::Vector2f ratio = deltaPos / hypotenusa;
	CalculateProgress(aTime);

	if (myEasing >= 0.99f)
	{
		myApBoxState = eAPBoxState::eGoingDown;
		myMovementTimer = 0.f;
	}
	else
	{
		CU::Vector2f changeFactor = myGoalPosition - myOriginalPosition;
		changeFactor = changeFactor * CU::Matrix33f::CreateRotateAroundZ(0.785f);
		myPosition =
		{
			myOriginalPosition.x + changeFactor.x * myEasing,
			myOriginalPosition.y + changeFactor.y * myEasing,
		};
	}
}

void APBox::MoveDown(const CommonUtilities::Time aTime)
{
	myGoalPosition = myTilePositionf;
	myOriginalPosition = myTilePositionf;
	myOriginalPosition.x = myTilePositionf.x + 0.1f;

	CU::Vector2f deltaPos =
	{
		myPosition.x - myGoalPosition.x,
		myPosition.y - myGoalPosition.y
	};

	float hypotenusa = sqrt(pow(deltaPos.y, 2));
	CU::Vector2f ratio = deltaPos / hypotenusa;
	CalculateProgress(aTime);

	if (myEasing >= 0.99f)
	{
		myApBoxState = eAPBoxState::eGoingUp;
		myMovementTimer = 0.f;
	}
	else
	{
		CU::Vector2f changeFactor = myGoalPosition - myOriginalPosition;
		changeFactor = changeFactor * CU::Matrix33f::CreateRotateAroundZ(0.785f);
		myPosition =
		{
			myOriginalPosition.x + changeFactor.x * myEasing,
			myOriginalPosition.y + changeFactor.y * myEasing,
		};
	}
}

void APBox::Animate(const CU::Time& aDelta)
{
	myApBoxState == eAPBoxState::eGoingUp ? MoveUp(aDelta) : MoveDown(aDelta);
}

void APBox::Reset()
{
	myPosition = myTilePositionf;
}

void APBox::Draw() const
{
	mySprite->Draw(myPosition);

	RenderConverter::AddRenderCommand(RenderCommand(*myAPText, 1.f, static_cast<unsigned short>(enumRenderLayer::eGUI)));
}
