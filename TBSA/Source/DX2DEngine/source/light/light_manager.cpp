#include "stdafx.h"
#include "light/light_manager.h"
#include "engine.h"
#include "render/Renderer.h"

using namespace DX2D;

CLightManager::CLightManager()
{
	myAmbientLight = 1.0f;
}

CLightManager::~CLightManager()
{
}

void CLightManager::AddLightToRender(const CLight* aLight)
{
	if (myLightsToRender.size() >= 8)
	{
		ERROR_PRINT("%s", "We only allow 8 lights at the same time and you are trying to push more");
		return;
	}
	myLightsToRender.push_back(aLight);
}

void DX2D::CLightManager::PostFrameUpdate()
{
	myLightsToRender.clear();
}

void DX2D::CLightManager::SetAmbience(float aAmbientLight)
{
	myAmbientLight = aAmbientLight;
}