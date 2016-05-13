#include "stdafx.h"
#include "Shaders.h"


Shaders::Shaders()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new Shaders();
	}
}

Shaders::~Shaders()
{
}

Shaders* Shaders::GetInstance()
{
	if (ourInstance != nullptr)
	{
		return ourInstance;
	}
}

void Shaders::ApplyShader(TileData* aTile, const std::string& aShader)
{

}

void Shaders::RemoveShader(TileData* aTile, const std::string& aShader)
{

}
