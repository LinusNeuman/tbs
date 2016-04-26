#pragma once

namespace DX2D
{
	class CLight
	{
	public:
		CLight();
		~CLight();
		void Render();
		Vector2f myPosition;
		Vector4f myColor;
		float myIntensity;
		float myFallOff;
	};
}