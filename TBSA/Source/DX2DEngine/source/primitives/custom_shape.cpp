#include "stdafx.h"
#include "primitives/custom_shape.h"
#include "engine.h"
#include "render/Renderer.h"
#include "texture/texture_manager.h"

using namespace DX2D;
CCustomShape::CCustomShape()
{
	myIndex = 0;
	myIsDirty = false;
	myTexture = nullptr;
}


CCustomShape::~CCustomShape()
{
}

void CCustomShape::Reset()
{
	myPoints.clear();
}

int CCustomShape::AddPoint(DX2D::Vector2f aPoint, CColor aColor, DX2D::Vector2f aUV)
{
	SCustomPoint point;
	point.myPosition = aPoint;
	point.myColor = aColor;
	point.myIndex = myIndex;
	point.myUV = aUV;
	myPoints.push_back(point);
	if (myPoints.size()%3 == 0)
	{
		myIndex++;
	}
	
	myIsDirty = true;
	return point.myIndex;
}

// Do this second
void CCustomShape::BuildShape()
{
	if (myPoints.size() %3 != 0)
	{
		INFO_PRINT("%s", "CCustomShape::BuildShape(): building shape with non even devided by 3 points, invalid! We need it to build triangles!");
		return;
	}
	if (!myTexture)
	{
		myTexture = CEngine::GetInstance()->GetTextureManager().GetWhiteSquareTexture();
	}
	myIsDirty = false;
}

void DX2D::CCustomShape::SetColorOnPoint(int aIndex, CColor aColor)
{
	for (size_t i = myPoints.size() - 1; i > 0; i--)
	{
		if (myPoints[i].myIndex == aIndex)
		{
			myPoints[i].myColor = aColor;
		}
	}
}

void DX2D::CCustomShape::RemovePoints(int aIndex)
{
	for (size_t i = myPoints.size() - 1; i > 0; i--)
	{
		if (myPoints[i].myIndex == aIndex)
		{
			myPoints.erase(myPoints.begin() + i);
			myIsDirty = true;
		}
	}
}

void DX2D::CCustomShape::Render()
{
	if (myIsDirty)
	{
		INFO_PRINT("%s", "CCustomShape::Render() shape is dirty, please call CCustomShape::BuildShape() to verify shape");
		return;
	}
	CEngine::GetInstance()->GetRenderer().AddToRender(this);
}

void DX2D::CCustomShape::SetTexture(const char* aPath)
{
	myTexture = CEngine::GetInstance()->GetTextureManager().GetTexture(aPath);
}
