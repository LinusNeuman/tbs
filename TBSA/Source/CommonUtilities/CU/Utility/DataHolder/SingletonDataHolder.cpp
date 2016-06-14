#include "stdafx.h"
#include "SingletonDataHolder.h"

SingletonDataHolder * SingletonDataHolder::ourInstance = nullptr;

SingletonDataHolder::SingletonDataHolder()
{
}


SingletonDataHolder::~SingletonDataHolder()
{
}

void SingletonDataHolder::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new SingletonDataHolder();
	}
}

void SingletonDataHolder::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void SingletonDataHolder::SetTargetResolution(const CU::Vector2ui & aTargetResolution)
{
	GetInstance().myTargetResolution = aTargetResolution;
	GetInstance().myTargetResolutionRatio = FLOATCAST(aTargetResolution.x) / FLOATCAST( aTargetResolution.y);
}

const CU::Vector2ui & SingletonDataHolder::GetTargetResolution()
{
	return GetInstance().myTargetResolution;
}

CU::Vector2f SingletonDataHolder::GetTargetResolutionf()
{
	return{ FLOATCAST(GetInstance().myTargetResolution.x), FLOATCAST(GetInstance().myTargetResolution.y) };
}

float SingletonDataHolder::GetTargetResolutionRatio()
{
	return GetInstance().myTargetResolutionRatio;
}

