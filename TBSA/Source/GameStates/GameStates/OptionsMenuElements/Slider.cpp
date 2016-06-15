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
	mySlider = new DX2D::CSprite(aSpriteArguments.mySliderPath);
	myKnobRegular = new DX2D::CSprite(aSpriteArguments.myKnobPath);
	myKnobHovered = new DX2D::CSprite(aSpriteArguments.myKnobHoveredPath);
	myKnobPressed = new DX2D::CSprite(aSpriteArguments.myKnobPressedPath);

	myKnob = myKnobRegular;
}

void Slider::InitPositions(SliderPositionArguments &aPositionsArguments)
{
	myKnobRegular->SetPivot(aPositionsArguments.myKnobPivot);
	myKnobHovered->SetPivot(aPositionsArguments.myKnobPivot);
	myKnobPressed->SetPivot(aPositionsArguments.myKnobPivot);

	mySlider->SetPosition(aPositionsArguments.mySliderPosition);
	myKnobRegular->SetPosition(aPositionsArguments.myKnobPosition);
	myKnobHovered->SetPosition(aPositionsArguments.myKnobPosition);
	myKnobPressed->SetPosition(aPositionsArguments.myKnobPosition);
}

float Slider::ConvertValueToPosition()
{
	float finalPosition;

	float beginPos = mySlider->GetPosition().x;
	float endPos = mySlider->GetPosition().x + 0.171875f;

	finalPosition = beginPos + (myValue * (endPos - beginPos));

	return finalPosition;
}

float Slider::ConvertPositionToValue(float aPos)
{
	float finalValue;

	float beginPos = mySlider->GetPosition().x;
	float endPos = mySlider->GetPosition().x + 0.171875f;

	
	finalValue = (aPos - beginPos) / (endPos - beginPos);

	return finalValue;
}

void Slider::SetAllKnobs(float aPos)
{
	if (aPos < mySlider->GetPosition().x)
	{
		aPos = mySlider->GetPosition().x;
	}
	myKnob->SetPosition({aPos, myKnob->GetPosition().y });
	myKnobRegular->SetPosition({ aPos, myKnob->GetPosition().y });
	myKnobHovered->SetPosition({ aPos, myKnob->GetPosition().y });
	myKnobPressed->SetPosition({ aPos, myKnob->GetPosition().y });
}

void Slider::Update(float)
{
	SetAllKnobs(ConvertValueToPosition());
	ProgressGet();

	if (myIsDraggingKnob == true)
	{

		myKnob = myKnobPressed;

		if (SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x > mySlider->GetPosition().x + 0.171875f)
		{
			myValue = 1.0f;
			SetAllKnobs(ConvertValueToPosition());
		}
		else if (SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x < mySlider->GetPosition().x)
		{
			myValue = 0.0f;
			SetAllKnobs(ConvertValueToPosition());
		}
		else
		{
			myKnob->SetPosition({ SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x, myKnob->GetPosition().y });
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
	if (SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x >= myKnob->GetPosition().x - myKnob->GetSize().x / 2 &&
		SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().x <= myKnob->GetPosition().x + myKnob->GetSize().x / 2)
	{
		if (SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().y + 0.010f >= myKnob->GetPosition().y - myKnob->GetSize().y / 2 &&
			SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace().y - 0.010f <= myKnob->GetPosition().y + myKnob->GetSize().y / 2)
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
	mySlider->Render();

	myKnob->Render();
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
