#pragma once


namespace DX2D
{
	class Vector4f
	{
	public:
		Vector4f(){}
		Vector4f(float aX, float aY, float aZ, float aW = float(1)) { x = aX; y = aY; z = aZ; w = aW; }
		Vector4f(const Vector4f& aVector) { x = aVector.x; y = aVector.y; z = aVector.z; w = aVector.w; }
		void Set(float aX, float aY, float aZ, float aW = float(1)) { x = aX; y = aY; z = aZ; w = aW; }
		float x;
		float y;
		float z;
		float w;
	};
}

