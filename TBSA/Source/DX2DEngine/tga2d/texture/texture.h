/*
This class will store a texture bound to DX11
*/
#pragma once
#include <tga2d\math\vector2.h>
#include <tga2d\math/color.h>

struct ID3D11ShaderResourceView;
struct ID3D11RenderTargetView;
namespace DX2D
{
	
	class CTexture
	{
	public:
		CTexture();
		~CTexture();

	public:
		std::string myPath;
		ID3D11ShaderResourceView* myResource;
		Vector2f mySize;
		Vector2<unsigned int> myImageSize;
		bool myIsFailedTexture;
		bool myIsReleased;

		CColor GetPixelColor(unsigned short aX, unsigned short aY, bool aRefreshData = false);
	private:
		BYTE* GrabPixelColors();
		BYTE* myPixelColors;
		bool myHasGrabbedColorData;
	};

	
	class CRendertarget : public CTexture
	{
	public:
		CRendertarget();
		~CRendertarget();

	public:
		ID3D11RenderTargetView* myTarget;
	};
}
