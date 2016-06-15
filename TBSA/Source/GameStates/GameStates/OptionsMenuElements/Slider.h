#pragma once
#include "tga2d\sprite\sprite.h"
#include <Audio/Instances/SoundEffect.h>
#include <Rend/StaticSprite.h>

// Simplifies argument sending and initializing. They only need different positions. // Linus
struct SliderSpriteArguments
{
	const char* mySliderPath = "Sprites/GUI/OptionsMenu/Slider.dds";
	const char* myKnobPath = "Sprites/GUI/OptionsMenu/Knob.dds";
	const char* myKnobPressedPath = "Sprites/GUI/OptionsMenu/KnobPressed.dds";
	const char* myKnobHoveredPath = "Sprites/GUI/OptionsMenu/KnobHovered.dds";
};
struct SliderPositionArguments
{
	CU::Vector2f mySliderPosition;
	CU::Vector2f myKnobPosition;
	CU::Vector2f myKnobPivot;
};
struct SliderSetOfArguments
{
	SliderSpriteArguments mySpriteArguments;
	SliderPositionArguments myPositionArguments;
};


class Slider
{
public:
	Slider();

	virtual void InitValue() = 0;
	void InitSprites(SliderSpriteArguments &aSpriteArguments);
	void InitPositions(SliderPositionArguments &aPositionsArguments);

	void Update(float aDeltaTime);
	void Render() const;

	CU::Vector2f GetSliderPosition(){ return mySliderPos; };
	CU::Vector2f GetKnobPosition(){ return myKnobPos; };

	CU::Vector2f GetSliderSize(){ return mySlider->GetSize(); };	
	CU::Vector2f GetKnobSize(){ return myKnob->GetSize(); };
	virtual ~Slider();
protected:
	StaticSprite* mySlider;
	CU::Vector2f mySliderPos;
	StaticSprite* myKnob;
	CU::Vector2f myKnobPos;
	StaticSprite* myKnobRegular;
	CU::Vector2f myKnobRegularPos;
	StaticSprite* myKnobPressed;
	CU::Vector2f myKnobPressedPos;
	StaticSprite* myKnobHovered;
	CU::Vector2f myKnobHoveredPos;

	DX2D::Vector2f myValueConvertedToPosition;
	float myValue;

	bool myIsHoveringKnob;
	bool myIsDraggingKnob;

	bool OnMouseClick();
	bool OnMouseHover();

	float ConvertValueToPosition();
	float ConvertPositionToValue(float aPos);
	void SetAllKnobs(float aPos);
	virtual void SliderSpecificUpdate() = 0;

	virtual void ProgressSet() = 0;
	virtual void ProgressGet() = 0;

	SoundEffect* myClickSound;
	SoundEffect* myHoverSound;
};

