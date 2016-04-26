#include "stdafx.h"
#include "texture/Texture.h"
#include "DirectXTK/Inc/ScreenGrab.h"

DX2D::CTexture::CTexture()
{
	myPath = "undefined";
	myResource = nullptr;
	myIsFailedTexture = false;
}

DX2D::CTexture::~CTexture()
{
	if (myIsFailedTexture)
	{
		return;
	}
	SAFE_RELEASE(myResource);
	myResource = nullptr;
	myPath = "undefined";
	SAFE_ARRAYDELETE(myPixelColors);
}

DX2D::CColor DX2D::CTexture::GetPixelColor(unsigned short aX, unsigned short aY, bool aRefreshData)
{
	CColor retColor;

	if (aX >= myImageSize.x
		||
		aY >= myImageSize.y)
	{
		ERROR_PRINT("%s%i%s%i%s%i%s%i", "GetPixelColor out of bounds! You want to get a pixel from: X", aX, " Y", aY, " but the image is: X", myImageSize.x - 1, " Y", myImageSize.y - 1);
		return retColor;
	}
	if (aRefreshData)
	{
		SAFE_DELETE(myPixelColors);
		myHasGrabbedColorData = false;
	}
	if (!myPixelColors && myHasGrabbedColorData)
	{
		return retColor;
	}
	if (!myPixelColors && !myHasGrabbedColorData)
	{
		myPixelColors = GrabPixelColors();
		myHasGrabbedColorData = true;
		if (!myPixelColors)
		{
			ERROR_PRINT("%s%s", "GetPixelColor can only grab data from a .DDS with format: A8R8G8B8! File:", myPath.c_str());
			return retColor;
		}
	}

	unsigned int pixelPlace = aX + (aY * myImageSize.x);

	pixelPlace *= 4;

	retColor.myA = myPixelColors[pixelPlace + 3];
	retColor.myR = myPixelColors[pixelPlace + 2];
	retColor.myG = myPixelColors[pixelPlace + 1];
	retColor.myB = myPixelColors[pixelPlace + 0];


	return retColor;
}

BYTE* DX2D::CTexture::GrabPixelColors()
{
	ID3D11Resource* resource = NULL;;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	if (myResource)
	{
		myResource->GetResource(&resource);
		myResource->GetDesc(&srvDesc);
	}
	else
	{
		return nullptr;
	}

	ID3D11Texture2D* tex = (ID3D11Texture2D*)resource;
	BYTE* bytes = nullptr;
	if (tex)
	{
		bytes = DirectX::GrabPixelData(CEngine::GetInstance()->GetDirect3D().GetContext(), tex);
	}


	return bytes;

}


DX2D::CRendertarget::CRendertarget() : CTexture()
{
	myTarget = nullptr;
}

DX2D::CRendertarget::~CRendertarget()
{
	SAFE_RELEASE(myTarget)
}