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
	mySprite->SetRenderPriority(100.f);

	myEasing = 0.f;
	myMovementTimer = 0.f;
	myMovementTotalDown = 1.0f;
	myMovementTotalUp = 1.0f;

	myApBoxState = eAPBoxState::eGoingUp;

	myOffset = { 0.f, 0.f };
}

APBox::~APBox()
{
	//SAFE_DELETE(myAPText);
	//SAFE_DELETE(mySprite);
}

void APBox::Update()
{

}

void APBox::CalculateProgress(const CommonUtilities::Time& aTime)
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

void APBox::MoveUp(const CommonUtilities::Time& aTime)
{
	CalculateProgress(aTime);

	if (myEasing >= 0.99f)
	{
		myApBoxState = eAPBoxState::eGoingDown;
		myMovementTimer = 0.f;
	}
	else
	{
		myPosition = myTilePositionf;
		myOffset = CU::Vector2f::One * ((0.2f * (1.f - myEasing)));
	}
}

void APBox::MoveDown(const CommonUtilities::Time& aTime)
{
	CalculateProgress(aTime);

	if (1.f - myEasing <= 0.01f)
	{
		myApBoxState = eAPBoxState::eGoingUp;
		myMovementTimer = 0.f;
	}
	else
	{
		myPosition = myTilePositionf;
		myOffset = CU::Vector2f::One * ((0.2f * myEasing));
	}
}

void APBox::Animate(const CU::Time& aDelta)
{
	myApBoxState == eAPBoxState::eGoingUp ? MoveUp(aDelta) : MoveDown(aDelta);
}

void APBox::Reset()
{
	myPosition = myTilePositionf;
	myOffset = {0.f,0.f};
	myApBoxState = eAPBoxState::eGoingDown;
	myMovementTimer = 0.f;
}

void APBox::Draw() const
{
	mySprite->Draw(myPosition - myOffset);

	RenderConverter::AddRenderCommandPutInCameraSpaceAndNormalize(RenderCommand(*myAPText, 1000.f, static_cast<unsigned short>(enumRenderLayer::eGUI)));
}
