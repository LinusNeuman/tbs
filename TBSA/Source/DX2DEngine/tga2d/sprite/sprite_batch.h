#pragma once
#include <vector>
#include <tga2d/shaders/shader_common.h>
#include <tga2d/render/render_common.h>


namespace DX2D
{
	class CSprite;
	class CTexturedQuadBatch;
	class CSpriteBatch
	{
	public:
		CSpriteBatch(bool aDeleteSpritesWhenDestructed);
		~CSpriteBatch();
		void Init(const char* aTexturePath = nullptr);
		bool AddObject(CSprite* aSpriteObject);
		void RemoveObject(CSprite* aSpriteObject, bool aAlsoDelete = false);

		void Render();

		void DeleteAll();

		void SetEffect(SEffect aEffect);
		SEffect GetEffect() const { return myEffect; }
		void ClearAll();

		void SetMap(EShaderMap aMapType, const char* aPath);

		CSprite* GetNext();
		void ResetNext();

		std::vector<std::vector<CSprite*>> mySprites;
		std::vector<CSprite*>* myCurrentSpriteAdder;
		CTexturedQuadBatch* myQuadBatch;
		Vector2f GetInitialSize();
		DX2D::Vector2<unsigned int> GetImageSize();
		const std::string GetImagePath() const;
	private:
		unsigned short myCurrentSpriteCount;
		unsigned short myNextIndex;
		unsigned short myNextBatch;
		SEffect myEffect;
		bool myDeleteSpritesOnDestruct;
	};

}

