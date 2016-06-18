#include "Tooltip.h"
#include <Input/SingletoIsometricInputWrapper/SingletonIsometricInputWrapper.h>
#include <Rend/RenderConverter.h>
#include <Rend/RenderCommand.h>


Tooltip::Tooltip()
{
	myText = new DX2D::CText("Text/erasdust.ttf_sdf");
	myText->myText = "";

	myIsTriggered = false;

	myCurrentTimeDelayed = 0.f;

	myShouldShow = false;
}


Tooltip::~Tooltip()
{
}

void Tooltip::Init(const char* aText, CU::Vector2i aSizeInPixels, float aShowDelay)
{
	myText->myText = aText;
	mySizeInPixels = aSizeInPixels;
	myTimeUntilShow = aShowDelay;

	myBackground = new StaticSprite();
	//myBackground->Init("Sprites/GUI/Tooltip/BackgroundPixel.dds", false);
	myBackground->Init("Sprites/GUI/Tooltip/BackgroundStatic.dds", false, CU::Vector4f::Zero, { 0.f, 0.0f });
	myBackground->SetLayer(enumRenderLayer::eGUI);
	myBackground->SetRenderPriority(3500.f);
	myBackground->SetColor({ 1, 1, 1, 0 });

	myTextColor = {1,1,1,0};
}

void Tooltip::Show()
{
	if (myText->myText == "")
	{
		return;
	}

	myIsTriggered = true;
}

void Tooltip::Close()
{
	if (myText->myText == "")
	{
		return;
	}

	Reset();
}

void Tooltip::Update(const CU::Time& aDelta)
{
	if (myText->myText == "")
	{
		return;
	}

	if (myIsTriggered == true && myShouldShow == false)
	{
		myCurrentTimeDelayed += aDelta.GetSeconds();
		if (myCurrentTimeDelayed >= myTimeUntilShow)
		{
			myShouldShow = true;
			myCurrentTimeDelayed = 0.f;
		}
	}
	else if (myIsTriggered == false && myShouldShow == true)
	{
		// fade down

		CU::Vector4f color = myBackground->GetColor();
		if (color.w >= 0.0f)
		{
			color.w -= 8.5f * aDelta.GetSeconds();
			if (color.w < 0)
			{
				color.w = 0;
				myShouldShow = false;
			}
			myBackground->SetColor(color);
			myTextColor = color;
		}
	}
	else if (myIsTriggered == true && myShouldShow == true)
	{
		CU::Vector4f color = myBackground->GetColor();
		if (color.w < 1.1f)
		{
			color.w += 5.5f * aDelta.GetSeconds();
			if (color.w  > 1)
			{
				color.w = 1;
			}
			myBackground->SetColor(color);
			myTextColor = color;
		}
	}
}

void Tooltip::Render()
{
	if (myShouldShow == true)
	{
		// render

		myBackground->DrawWithNormalized({ IsometricInput::GetMouseWindowPositionNormalizedSpace().x + 0.0025f, IsometricInput::GetMouseWindowPositionNormalizedSpace().y - 0.055f });

		TextRenderData data;
		data.myText = myText->myText;
		data.myPos = { IsometricInput::GetMouseWindowPositionNormalizedSpace().x + 0.0025f, IsometricInput::GetMouseWindowPositionNormalizedSpace().y - 0.0333f };
		data.myColor = myTextColor;

		RenderConverter::AddRenderCommand(RenderCommand(3600.f, static_cast<unsigned short>(enumRenderLayer::eGUI), data, false, true));
	}
}

void Tooltip::Reset()
{
	myIsTriggered = false;
	myCurrentTimeDelayed = 0.f;
}
