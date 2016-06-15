#include "stdafx.h"
#include "Options.h"


Options::Options()
{
}

void Options::Initialize()
{
	myIsActive = true;
	myMouseWasInvisible = false;

	myBackground = new StaticSprite();
	myBackground->Init("Sprites/GUI/OptionsMenu/Background.dds", false, CU::Vector4f::Zero, { 0.5f, 0.5f });
	myBackground->SetLayer(enumRenderLayer::eGUI);
	myBackground->SetRenderPriority(2000);

	myPosition = {0.5f, 0.5f};

	SliderSetOfArguments SliderArgsSFX;
	SliderSetOfArguments SliderArgsMusic;

	mySFXSlider.InitSprites(SliderArgsSFX.mySpriteArguments);
	myMusicSlider.InitSprites(SliderArgsMusic.mySpriteArguments);

	SliderArgsSFX.myPositionArguments.mySliderPosition = { 0.5f - (0.171875f / 2), myPosition.y + 0.15f };
	SliderArgsMusic.myPositionArguments.mySliderPosition = { 0.5f - (0.171875f / 2), myPosition.y - 0.004f };

	SliderArgsSFX.myPositionArguments.myKnobPivot = {0.5f, 0.5f};
	SliderArgsMusic.myPositionArguments.myKnobPivot = { 0.5f, 0.5f };

	mySFXSlider.InitPositions(SliderArgsSFX.myPositionArguments);
	myMusicSlider.InitPositions(SliderArgsMusic.myPositionArguments);

	SliderArgsSFX.myPositionArguments.myKnobPosition = { mySFXSlider.GetSliderPosition().x + 0.171875f, mySFXSlider.GetSliderPosition().y + mySFXSlider.GetSliderSize().y / 2 };
	SliderArgsMusic.myPositionArguments.myKnobPosition = { myMusicSlider.GetSliderPosition().x + 0.171875f, myMusicSlider.GetSliderPosition().y + myMusicSlider.GetSliderSize().y / 2 };

	mySFXSlider.InitPositions(SliderArgsSFX.myPositionArguments);
	myMusicSlider.InitPositions(SliderArgsMusic.myPositionArguments);
}

void Options::Update(float aDeltaTime)
{
	if (myIsActive == true)
	{
		myMusicSlider.Update(aDeltaTime);
		mySFXSlider.Update(aDeltaTime);
	}
}

void Options::Render() const
{
	if (myIsActive == true)
	{
		myBackground->DrawWithNormalized(myPosition);

		myMusicSlider.Render();
		mySFXSlider.Render();
	}
}

Options::~Options()
{
	SAFE_DELETE(myBackground);
}
