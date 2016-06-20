#include "stdafx.h"
#include "APBox.h"
#include <Rend/RenderConverter.h>
#include <Rend/RenderCommand.h>
#include <CU/Matriser/matrix.h>

const CU::Vector4f CantAffordColor = {1.f, 0.f, 0.f, 1.f};
const CU::Vector4f PathColor = { 1.f, 0.5f, 0.5f, 1.f };
const CU::Vector4f AttackColor = { 0.f, 1.f, 0.f, 1.f };
const CU::Vector4f NeutralColor = { 1.f, 1.f, 1.f, 1.f };
const CU::Vector4f PositiveColor = { 0.f, 1.f, 0.f, 1.f };

APBox::APBox()
{
	myIsInitedFully = false;

	myAPText = new DX2D::CText("Text/calibril.ttf_sdf");

	mySpriteSelected = new StaticSprite();
	mySpriteSelected->Init("Sprites/GUI/HUD/AP/ActorAPSelected.dds", true, CU::Vector4f::Zero, { 0.5f, 0.5f });
	mySpriteSelected->SetLayer(enumRenderLayer::eGUI);
	mySpriteSelected->SetPivotWithPixels({ mySpriteSelected->GetSizeInPixels().x / 2.f, -(mySpriteSelected->GetSizeInPixels().y / 2.f) });
	mySpriteSelected->SetRenderPriority(100.f);

	mySpriteUnSelected = new StaticSprite();
	mySpriteUnSelected->Init("Sprites/GUI/HUD/AP/ActorAP.dds", true, CU::Vector4f::Zero, { 0.5f, 0.5f });
	mySpriteUnSelected->SetLayer(enumRenderLayer::eGUI);
	mySpriteUnSelected->SetPivotWithPixels({ mySpriteUnSelected->GetSizeInPixels().x / 2.f, -(mySpriteUnSelected->GetSizeInPixels().y / 2.f) });
	mySpriteUnSelected->SetRenderPriority(100.f);

	mySprite = mySpriteUnSelected;

	myEasing = 0.f;
	myAP = 0;
	myCurrentCost = 0;
	myMovementTimer = 0.f;
	myMovementTotalDown = 1.0f;
	myMovementTotalUp = 1.0f;

	myApBoxState = eAPBoxState::eGoingUp;

	myOffset = { 0.f, 0.f };

	myIsInitedFully = true;

	myIsSelected = false;
}

APBox::~APBox()
{
	//SAFE_DELETE(myAPText);
	//SAFE_DELETE(mySprite);
}

void APBox::Update()
{
	myColor = PathColor;

	int tempValue = INTCAST(myAP) - INTCAST(myCurrentCost);
	myAPText->myText = std::to_string(tempValue);

	if (myCurrentCost > 0)
	{
		if (myCurrentCost > myAP)
		{
			myColor = CantAffordColor;
		}
		
		myColor = PathColor;
	}
	else if (myCurrentCost < 0)
	{
		myColor = PositiveColor;
	}
	else
	{
		myColor = NeutralColor;
	}
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
	mySprite = mySpriteSelected;
	myApBoxState == eAPBoxState::eGoingUp ? MoveUp(aDelta) : MoveDown(aDelta);
}

void APBox::Reset()
{
	myPosition = myTilePositionf;
	myOffset = {0.f,0.f};
	myApBoxState = eAPBoxState::eGoingDown;
	myMovementTimer = 0.f;
	mySprite = mySpriteUnSelected;
}

void APBox::Draw() const
{
	if (myIsInitedFully == false)
	{
		return;
	}


	mySprite->Draw(myPosition - myOffset);


	CU::Vector2f OffsetForText = mySprite->GetSizeInPixels();
	OffsetForText.y -= 16;
	OffsetForText.x = ((myAPText->GetWidth() / 2.f) * SingletonDataHolder::GetTargetResolution().x) - 1;
	OffsetForText = CU::PixelToIsometric(OffsetForText);

	TextRenderData data;
	data.myText = myAPText->myText;
	data.myPos = (myPosition - myOffset) - OffsetForText;
	data.myColor = myColor;

	RenderConverter::AddRenderCommandPutInCameraSpaceAndNormalize(RenderCommand(500.f, static_cast<unsigned short>(enumRenderLayer::eGUI), data));
}
