#include "stdafx.h"

#include "sprite/textured_quad_batch.h"
#include "sprite/sprite.h"
#include "engine.h"
#include "texture/texture_manager.h"
#include "render/renderer.h"
#include "d3d/direct_3d.h"

using namespace DX2D;

CTexturedQuadBatch::CTexturedQuadBatch(void)
{
	myEngine = CEngine::GetInstance();
	mySpriteBatch = nullptr;
	mySize.Set(1, 1);
}


CTexturedQuadBatch::~CTexturedQuadBatch(void)
{
}

void DX2D::CTexturedQuadBatch::Init(const char* aTexturePath)
{
	if (aTexturePath)
	{
		myTexturePath = aTexturePath;
		myTexture = myEngine->GetTextureManager().GetTexture(aTexturePath);
		mySize = myTexture->mySize;
	}
	else
	{
		myTexture = myEngine->GetTextureManager().GetWhiteSquareTexture();
	}
}

void DX2D::CTexturedQuadBatch::Render(CSpriteBatch* aBatch)
{
	mySpriteBatch = aBatch;
	myEngine->GetRenderer().AddToRender(this);
}

void DX2D::CTexturedQuadBatch::Draw(CDirectEngine* aRenderer)
{
	aRenderer->DoDraw(this);
}

void DX2D::CTexturedQuadBatch::SetMap(EShaderMap aMapType, const char* aPath)
{
	myMaps[aMapType] = myEngine->GetTextureManager().GetTexture(aPath);
}
