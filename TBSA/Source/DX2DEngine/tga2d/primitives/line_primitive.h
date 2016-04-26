#pragma once

#include "tga2d/render/render_object.h"


namespace DX2D
{
	class CEngine;
	class CDirectEngine;
	class LinePrimitive : public CRenderObjectLine
	{
	public:
		LinePrimitive(void);
		~LinePrimitive(void);
		void Render();
		void SetFrom(float aX, float aY)
		{
			myFromPosition.Set(aX, aY);
		}
		void SetTo(float aX, float aY)
		{
			myToPosition.Set(aX, aY);
		}
	private:
	};

	class CLineMultiPrimitive : public CRenderObject
	{
	public:
		CLineMultiPrimitive(void){}
		~CLineMultiPrimitive(void){}
		void Render();
		void Draw(CDirectEngine* aRenderer) override;
		CColor *myColor;
		Vector2f *myFromPosition;
		Vector2f *myToPosition;
		unsigned int myCount;
	};
}