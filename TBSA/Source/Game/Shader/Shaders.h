#pragma once
#include <unordered_map>

class TileData;

class Shaders
{
public:
	static Shaders* GetInstance();
	void AddShader(/*Shader& aShader*/);
	void ApplyShader(TileData* aTile, const std::string& aShader);
	void RemoveShader(TileData* aTile, const std::string& aShader);
private:
	Shaders();
	~Shaders();
	static Shaders* ourInstance;
	std::unordered_map<std::string/*Shader aShader*/, void*> myShaders;
	//CustomShaderContainer
};

