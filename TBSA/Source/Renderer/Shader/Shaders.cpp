#include "stdafx.h"
#include "Shaders.h"
#include <Rend\StaticSprite.h>
#include <tga2d\shaders\customshader.h>
#include <tga2d\texture\texture_manager.h>
#include "tga2d/sprite/sprite.h"

Shaders* Shaders::ourInstance = nullptr;


Shaders::Shaders()
{
}

Shaders::~Shaders()
{
}

Shaders* Shaders::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "Shader ourinstance is nullptrs");

	return ourInstance;
}

void Shaders::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new Shaders();
	}
}

void Shaders::AddShader(DX2D::CCustomShader* aShader, const std::string& aName)
{
	Shader* tempShader = new Shader(aShader, aName);
	myShaders[tempShader->myName] = tempShader;
}

void Shaders::ApplyShader(StaticSprite* aSprite, const std::string& aShader)
{
	aSprite->GetSprite()->SetCustomShader(myShaders[aShader]->myShader);
}

void Shaders::RemoveShader(StaticSprite* aSprite)
{
	aSprite->GetSprite()->SetCustomShader(nullptr);
}

