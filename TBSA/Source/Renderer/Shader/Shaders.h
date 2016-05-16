#pragma once
#include <unordered_map>


class StaticSprite;

namespace DX2D
{
	class CCustomShader;
}

class Shaders
{
public:
	struct Shader
	{
		Shader(DX2D::CCustomShader* aShader, const std::string& aName)
		{
			myShader = aShader;
			myName = aName;
		}

		~Shader(){};
		DX2D::CCustomShader * myShader;
		std::string myName;
	};
	static Shaders* GetInstance();
	static void Create();
	void AddShader(DX2D::CCustomShader* aShader, const std::string& aName);
	void ApplyShader(StaticSprite* aSprite, const std::string& aShader);
	void RemoveShader(StaticSprite* aSprite);
private:
	Shaders();
	~Shaders();
	static Shaders* ourInstance;
	std::unordered_map<std::string, Shader*> myShaders;
};

