#include "Tooltip.h"
#include <Input/SingletoIsometricInputWrapper/SingletonIsometricInputWrapper.h>
#include <Rend/RenderConverter.h>
#include <Rend/RenderCommand.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>


Tooltip::Tooltip()
{
	myBackground = nullptr;

	myText = new DX2D::CText("Text/erasdust.ttf_sdf");
	myText->myText = "";

	myIsTriggered = false;

	myCurrentTimeDelayed = 0.f;

	myShouldShow = false;
}


Tooltip::~Tooltip()
{
}

void Tooltip::Init(const char* aText, CU::Vector2i aSizeInPixels, float aShowDelay, float aTextOffset)
{
	myText->myText = aText;
	mySizeInPixels = aSizeInPixels;
	myTimeUntilShow = aShowDelay;
	myTextOffset = aTextOffset;

	myBackground = new StaticSprite();
	myBackground->Init("Sprites/GUI/Tooltip/BackgroundPixel.dds", false, CU::Vector4f::Zero, {0.f, 1.0f});
	//myBackground->Init("Sprites/GUI/Tooltip/BackgroundStatic.dds", false, CU::Vector4f::Zero, { 0.f, 0.0f });
	myBackground->SetLayer(enumRenderLayer::eGUI);
	myBackground->SetRenderPriority(3500.f);
	myBackground->SetColor({ 1.f, 1.f, 1.f, 0.f });
	myBackground->SetSizeMultiplier({ static_cast<float>(aSizeInPixels.x), static_cast<float>(aSizeInPixels.y) });

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

		myBackground->DrawWithNormalized({ IsometricInput::GetMouseWindowPositionNormalizedSpace().x + 0.0025f, IsometricInput::GetMouseWindowPositionNormalizedSpace().y });

		TextRenderData data;
		data.myText = myText->myText;
		data.myPos = { IsometricInput::GetMouseWindowPositionNormalizedSpace().x + 0.0035f, (IsometricInput::GetMouseWindowPositionNormalizedSpace().y - myTextOffset) - (mySizeInPixels.y / SingletonDataHolder::GetTargetResolution().y) };
		data.myColor = myTextColor;

		RenderConverter::AddRenderCommand(RenderCommand(3600.f, static_cast<unsigned short>(enumRenderLayer::eGUI), data, false, true));
	}
}

void Tooltip::Reset()
{
	myIsTriggered = false;
	myCurrentTimeDelayed = 0.f;
}

void Tooltip::ResetForStates()
{
	if (myBackground == nullptr)
	{
		return;
	}

	myIsTriggered = false;
	myCurrentTimeDelayed = 0.f;
	myShouldShow = false;

	myBackground->SetColor({ myBackground->GetColor().r, myBackground->GetColor().g, myBackground->GetColor().b, 0.f });
	myTextColor = myBackground->GetColor();
}