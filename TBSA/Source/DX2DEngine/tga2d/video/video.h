/*
Use this class to create and show a video
Limitations:
-Video must be in the windows media format (.wmv)
-No audio will be avalible at the moment (workaround: play a sound at the same time you play the video)
*/

#pragma once
#include <wtypes.h>

namespace DX2D
{
	class CVideoInstance;
	class CVideo
	{
	public:
		CVideo();
		~CVideo();
		void Init(WCHAR* szFileName);
		void Play();
		void Stop();
		void Render();
		void SetPosition(DX2D::Vector2f aPsoition);
		bool IsDone();
	private:
		CVideoInstance* myInstance;
	};


}
