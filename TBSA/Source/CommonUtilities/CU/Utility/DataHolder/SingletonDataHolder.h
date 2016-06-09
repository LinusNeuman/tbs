#pragma once
#include <CU/Vectors/vector2.h>

class SingletonDataHolder
{
public:
	static void Create();
	static void Destroy();

	static void SetTargetResolution(const CU::Vector2ui & aTargetResolution);
	static const CU::Vector2ui & GetTargetResolution();

private:
	CU::Vector2ui myTargetResolution;

	static SingletonDataHolder * ourInstance;

	static SingletonDataHolder & GetInstance();

	SingletonDataHolder();
	~SingletonDataHolder();
};

inline SingletonDataHolder & SingletonDataHolder::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "DataHolder instance is not created");
	return *ourInstance;
}

