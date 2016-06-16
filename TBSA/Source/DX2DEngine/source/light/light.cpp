#include "stdafx.h"
#include "light/light.h"
#include "engine.h"
#include "light/light_manager.h"

using namespace DX2D;

CLight::CLight()
	:myIntensity(100.0f)
{
	myPosition.Set(400, 400);
	myColor.Set(1, 1, 1, 1);
	myIntensity = 1;
	myFallOff = 1;
}


CLight::~CLight()
{
}

void DX2D::CLight::Render()
{
	CEngine::GetInstance()->GetLightManager().AddLightToRender(this);
}
