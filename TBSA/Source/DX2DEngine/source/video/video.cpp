#include "stdafx.h"
#include "video/video.h"
#include "video/video_instance.h"
#include "sprite/Sprite.h"

using namespace DX2D;
CVideo::CVideo()
{
}


CVideo::~CVideo()
{
	delete myInstance;
}

void CVideo::Init(WCHAR* szFileName)
{
	myInstance = new CVideoInstance();
	myInstance->Init(szFileName);
}

void DX2D::CVideo::Play()
{
	myInstance->Play();
}

void DX2D::CVideo::Stop()
{
	myInstance->Stop();
}

void DX2D::CVideo::Render()
{
	myInstance->Render();
}

void DX2D::CVideo::SetPosition(DX2D::Vector2f aPsoition)
{
	myInstance->mySprite->SetPosition(aPsoition);
}

bool DX2D::CVideo::IsDone()
{
	return myInstance->IsDone();
}

