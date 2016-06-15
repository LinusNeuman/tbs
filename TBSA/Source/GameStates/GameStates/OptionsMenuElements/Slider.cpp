#include "stdafx.h"
#include "Slider.h"
#include <Input/SingletoIsometricInputWrapper/SingletonIsometricInputWrapper.h>

Slider::Slider()
{
	myIsHoveringKnob = false;
	myIsDraggingKnob = false;

	myClickSound = new SoundEffect();
	myClickSound->Init("Sounds/GUI/HoverMenuItem2.ogg");

	myHoverSound = new SoundEffect();
	myHoverSound->Init("Sounds/GUI/HoverMenuItem.ogg");
}

void Slider::InitValue()
{

}

void Slider::InitSprites(SliderSpriteArguments &aSpriteArguments)
{
	mySlider = new StaticSprite();
	mySlider->Init(aSpriteArguments.mySliderPath, false);
	mySlider->SetLayer(enumRenderLayer::eGUI);
	mySlider->SetRenderPriority(2500);
	myKnobRegular = new StaticSprite();
	myKnobRegular->Init(aSpriteArguments.myKnobPath, false, CU::Vector4f::Zero, { 0.5f, 0.5f });
	myKnobRegular->SetLayer(enumRenderLayer::eGUI);
	myKnobRegular->SetRenderPriority(2600);
	myKnobHovered = new StaticSprite();
	myKnobHovered->Init(aSpriteArguments.myKnobHoveredPath, false, CU::Vector4f::Zero, { 0.5f, 0.5f });
	myKnobHovered->SetLayer(enumRenderLayer::eGUI);
	myKnobHovered->SetRenderPriority(2600);
	myKnobPressed = new StaticSprite();
	myKnobPressed->Init(aSpriteArguments.myKnobPressedPath, false, CU::Vector4f::Zero, { 0.5f, 0.5f });
	myKnobPressed->SetLayer(enumRenderLayer::eGUI);
	myKnobPressed->SetRenderPriority(2600);

	myKnob = myKnobRegular;
}

void Slider::InitPositions(SliderPositionArguments &aPositionsArguments)
{
	mySliderPos = (aPositionsArguments.mySliderPosition);
	myKnobRegularPos = (aPositionsArguments.myKnobPosition);
	myKnobHoveredPos = (aPositionsArguments.myKnobPosition);
	myKnobPressedPos = (aPositionsArguments.myKnobPosition);
	myKnobPos = myKnobRegularPos;
}

float Slider::ConvertValueToPosition()
{
	float finalPosition;

	float beginPos = mySliderPos.x;
	float endPos = mySliderPos.x + 0.171875f;

	finalPosition = beginPos + (myValue * (endPos - beginPos));

	return finalPosition;
}

float Slider::ConvertPositionToValue(float aPos)
{
	float finalValue;

	float beginPos = mySliderPos.x;
	float endPos = mySliderPos.x + 0.171875f;

	
	finalValue = (aPos - beginPos) / (endPos - beginPos);

	return finalValue;
}

void Slider::SetAllKnobs(float aPos)
{
	if (aPos < mySliderPos.x)
	{
		aPos = mySliderPos.x;
	}
	myKnobPos = {aPos, myKnobPos.y};
	myKnobRegularPos = { aPos, myKnobPos.y };
	myKnobHoveredPos = { aPos, myKnobPos.y };
	myKnobPressedPos = { aPos, myKnobPos.y };
}

void Slider::Update(float)
{
	SetAllKnobs(ConvertValueToPosition());
	ProgressGet();

	if (myIsDraggingKnob == true)
	{

		myKnob = myKnobPressed;

		if (SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x > mySliderPos.x + 0.171875f)
		{
			myValue = 1.0f;
			SetAllKnobs(ConvertValueToPosition());
		}
		else if (SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x < mySliderPos.x)
		{
			myValue = 0.0f;
			SetAllKnobs(ConvertValueToPosition());
		}
		else
		{
			myKnobPos = { SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x, myKnobPos.y };
			myValue = ConvertPositionToValue(SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x);
			SetAllKnobs(ConvertValueToPosition());
		}
	}
	else if (myIsHoveringKnob == true && myIsDraggingKnob == false)
	{
		myKnob = myKnobHovered;
	}
	else
	{


		myKnob = myKnobRegular;
	}

	if (OnMouseClick() == true)
	{
		myIsDraggingKnob = true;
		// do drag stuff
	}
	else
	{
		//  stop dragging
		myIsDraggingKnob = false;
	}

	if (OnMouseHover() == true)
	{
		myIsHoveringKnob = true;
	}
	else
	{
		if (myIsHoveringKnob == true)
		{
		}

		myIsHoveringKnob = false;
	}
	SliderSpecificUpdate();
	ProgressSet();
}

void Slider::ProgressGet()
{

}
void Slider::ProgressSet()
{

}

bool Slider::OnMouseHover()
{
	if (SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x >= myKnobPos.x - myKnob->GetSize().x / 2 &&
		SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x <= myKnobPos.x + myKnob->GetSize().x / 2)
	{
		if (SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().y + 0.010f >= myKnobPos.y - myKnob->GetSize().y / 2 &&
			SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().y - 0.010f <= myKnobPos.y + myKnob->GetSize().y / 2)
		{
			if (myIsHoveringKnob == false)
			{
				myHoverSound->Play(1.0f);
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool Slider::OnMouseClick()
{
	if (OnMouseHover() == true)
	{
		if (SingletonIsometricInputWrapper::GetMouseButtonDown(CommonUtilities::enumMouseButtons::eLeft) == true)
		{
			if (myIsDraggingKnob == false)
			{
				myClickSound->Play(1.0f);
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void Slider::SliderSpecificUpdate()
{

}

void Slider::Render() const
{
	mySlider->DrawWithNormalized(mySliderPos);

	myKnob->DrawWithNormalized(myKnobPos);
}


Slider::~Slider()
{
	SAFE_DELETE(mySlider);
	SAFE_DELETE(myKnobRegular);
	SAFE_DELETE(myKnobPressed);
	SAFE_DELETE(myKnobHovered);
	SAFE_DELETE(myClickSound);
	SAFE_DELETE(myHoverSound);
}
