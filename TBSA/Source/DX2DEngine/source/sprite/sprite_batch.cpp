#include "stdafx.h"

#include "sprite/sprite_batch.h"
#include "sprite/sprite.h"
#include "sprite/textured_quad.h"
#include "sprite/textured_quad_batch.h"
#include "texture/texture_manager.h"
#include "shaders/shader_common.h"

using namespace DX2D;

CSpriteBatch::CSpriteBatch(bool aDeleteSpritesWhenDestructed)
	:myQuadBatch(nullptr)
	, myDeleteSpritesOnDestruct(aDeleteSpritesWhenDestructed)
{
	myCurrentSpriteCount = 0;
	std::vector<CSprite*> newSpriteAdder;
	mySprites.push_back(newSpriteAdder);
	myNextIndex = 0;
	myNextBatch = 0;
	myEffect = SEffect_None;
}


CSpriteBatch::~CSpriteBatch(void)
{
	if (myDeleteSpritesOnDestruct)
	{
		DeleteAll();
	}
	delete myQuadBatch;
}

void CSpriteBatch::Init(const char* aTexturePath)
{
	if (myQuadBatch)
	{
		INFO_PRINT("%s%s", "Initing an already inited batch! Texture: ", aTexturePath);
		return;
	}
	myQuadBatch = new CTexturedQuadBatch();
	myQuadBatch->Init(aTexturePath);
}

bool CSpriteBatch::AddObject(CSprite* aSpriteObject)
{
	if (aSpriteObject->GetTexturedQuad()->myCustomShader)
	{
		INFO_PRINT("CSpriteBatch::AddObject() a sprite with a custom shader added. This will not work in a batch");
	}
	if (myCurrentSpriteCount > SPRITE_BATCH_COUNT)
	{
		std::vector<CSprite*> newSpriteAdder;
		mySprites.push_back(newSpriteAdder);
		myCurrentSpriteCount = 0;
	}
	if (!aSpriteObject)
	{
		return false;
	}
	aSpriteObject->myShouldRenderBatched = true;
	mySprites[mySprites.size()-1].push_back(aSpriteObject);
	myCurrentSpriteCount++;
	return true;
}


void DX2D::CSpriteBatch::RemoveObject(CSprite* aSpriteObject, bool aAlsoDelete)
{
	for (unsigned int i = 0; i < mySprites.size(); i++)
	{
		std::vector<CSprite*>& sprites = mySprites[i];
		std::vector<CSprite*>::iterator iter = sprites.begin();
		while (iter != sprites.end())
		{
			if (aSpriteObject == (*iter))
			{
				iter = sprites.erase(iter);
				if (aAlsoDelete)
				{
					SAFE_DELETE(aSpriteObject);
				}
				
				myCurrentSpriteCount--;
				myCurrentSpriteCount = MAX(myCurrentSpriteCount, 0);
			}
			else
			{
				++iter;
			}
		}
	}
}

void DX2D::CSpriteBatch::Render()
{
	if (!myCurrentSpriteCount)
	{
		return;
	}
	if (!myQuadBatch)
	{
		ERROR_AUTO_PRINT("%s", "SpriteBatch not inited! Can not render!");
		return;
	}

	myQuadBatch->Render(this);

}

CSprite* DX2D::CSpriteBatch::GetNext()
{
	if (myNextBatch > static_cast<int>(mySprites.size())-1)
	{
		return nullptr;
	}
	if (myNextIndex >  static_cast<int>(mySprites[myNextBatch].size()) - 1)
	{
		myNextIndex = 0;
		myNextBatch++;
		return GetNext();
	}

	CSprite* sprite = mySprites[myNextBatch][myNextIndex];
	myNextIndex++;
	return sprite;
}

void DX2D::CSpriteBatch::ResetNext()
{
	myNextIndex = 0;
	myNextBatch = 0;
}

Vector2f DX2D::CSpriteBatch::GetInitialSize()
{
	return myQuadBatch->myTexture->mySize;
}

Vector2<unsigned int> DX2D::CSpriteBatch::GetImageSize()
{
	return myQuadBatch->myTexture->myImageSize;
}

const std::string DX2D::CSpriteBatch::GetImagePath() const
{
	if (myQuadBatch && myQuadBatch->myTexture)
	{
		return myQuadBatch->myTexture->myPath;
	}

	return "";
	
}

void DX2D::CSpriteBatch::SetEffect(SEffect aEffect)
{
	myEffect = aEffect;
}

void DX2D::CSpriteBatch::ClearAll()
{
	for (unsigned int i = 0; i < mySprites.size(); i++)
	{
		std::vector<CSprite*>& sprites = mySprites[i];
		sprites.clear();
	}
	mySprites.clear();
	std::vector<CSprite*> newSpriteAdder;
	mySprites.push_back(newSpriteAdder);
	myCurrentSpriteCount = 0;
}

void DX2D::CSpriteBatch::SetMap(EShaderMap aMapType, const char* aPath)
{
	myQuadBatch->SetMap(aMapType, aPath);
}

void DX2D::CSpriteBatch::DeleteAll()
{
	for (unsigned int i = 0; i < mySprites.size(); i++)
	{
		std::vector<CSprite*>& sprites = mySprites[i];
		for (CSprite* sprite : sprites)
		{
			delete sprite;
		}
		sprites.clear();
	}
	mySprites.clear();
}