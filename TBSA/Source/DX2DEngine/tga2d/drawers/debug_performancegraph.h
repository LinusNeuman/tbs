#pragma once
#include <vector>

#define DEBUG_PERFGRAPH_SAMPLES 500
namespace DX2D
{
	class CText;
	class LinePrimitive;
	class CSprite;
	class CCustomShape;
	class CDebugDrawer;
	class CPerformanceGraph
	{
	public:
		CPerformanceGraph(CDebugDrawer* aDrawer);
		~CPerformanceGraph(void);
		void Init(DX2D::CColor& aBackgroundColor, DX2D::CColor& aLineColor, const std::string& aText);
		void Render();

		void FeedValue(int aValue);
	private:
		CCustomShape* myBackGround;
		std::vector<int> myBuffer;
		CDebugDrawer* myDrawer;
		DX2D::CColor myLineColor;
		CText* myText;

	};
}
