#pragma once

#include "render/render_object.h"
#include "render/render_common.h"


namespace DX2D
{
	class CTexture;
	class CSprite;
	class CEngine;
	class CSpriteBatch;
	class CTexturedQuadBatch : public CRenderObject
	{
	public:
		CTexturedQuadBatch(void);
		~CTexturedQuadBatch(void);
		void Init(const char* aTexturePath);

		/* Render the whole batch, if aRenderAll is false, the individual sprites can choose to be rendered or not, see CSprite::SetShouldRender() */
		void Render(CSpriteBatch* aBatch);
		
		CSpriteBatch* GetSpriteBatch() const{return mySpriteBatch;}
		CTexture* myTexture;
		Vector2f mySize;
		void SetMap(EShaderMap aMapType, const char* aPath);
		CTexture* myMaps[MAP_MAX];
	private:
		virtual void Draw(CDirectEngine* aRenderer);
		std::string myTexturePath;
		
		CEngine* myEngine;	
		CSpriteBatch* mySpriteBatch;
		
		
	};
}
