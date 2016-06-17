/*
This class handles all the textures created, please use this when you create a texture
*/

#pragma once
#include <vector>
#include "Texture.h"

struct ID3D11ShaderResourceView;
namespace DX2D
{
	class CDirectEngine;
	class CSprite;
	class CTextureManager
	{
	public:
		CTextureManager(void);
		~CTextureManager(void);
		void Init();
		CTexture* GetTexture(const char* aTexturePath);
		CRendertarget* GetRendertarget(const Vector2ui& aSize);
		CTexture* GetWhiteSquareTexture(){ return myWhiteSquareTexture; }
		Vector2f GetTextureSize(struct ID3D11ShaderResourceView* aResourceView, bool aNormalize = true) const;

		void ReleaseTexture(CTexture* aTexture);

		void Update();

		/* Requires DX11 includes */
		struct ID3D11ShaderResourceView* GetDefaultNormalMapResource() const { return myDefaultNormalMapResource; }
		/* Requires DX11 includes */
		struct ID3D11ShaderResourceView* GetNoiseTexture() const { return myNoiseResource; }
	private:
		std::vector<CTexture*> myResourceViews;
		void GeneratePerlinNoiseTexture(unsigned short aWidth, unsigned short aHeight);
		void CreateErrorSquareTexture();
		ID3D11ShaderResourceView* CreateWhiteSquareTexture();
		void CreateDefaultNormalmapTexture();
		
		struct ID3D11Texture2D *myNoiseTexture;
		struct ID3D11ShaderResourceView* myNoiseResource;
		struct ID3D11ShaderResourceView* myFailedResource;
		/*ID3D11ShaderResourceView* myWhiteSquareResource;*/
		struct ID3D11ShaderResourceView* myDefaultNormalMapResource;
		class CDirectEngine* myDirect3D;
		class CTexture* myWhiteSquareTexture;
	};
}