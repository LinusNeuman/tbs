#pragma once
#include <vector>



#define MAXSAMPLES 100
namespace DX2D
{

	class CText;
	class LinePrimitive;
	class CSprite;
	class CPerformanceGraph;
	class CLineMultiPrimitive;
	class CDebugDrawer
	{
	public:
		CDebugDrawer(int aFlagset);
		~CDebugDrawer(void);
		void Init();
		void Update(float aTimeDelta);
		void Render();
		void DrawLine(Vector2f aFrom, Vector2f aTo, Vector4f aColor = Vector4f(1, 1, 1, 1));
		void DrawLines(Vector2f* aFrom, Vector2f* aTo, CColor* aColor, unsigned int aCount);

		void DrawArrow(Vector2f aFrom, Vector2f aTo, Vector4f aColor = Vector4f(1, 1, 1, 1));
		void ShowErrorImage();
	private:
		double CalcAverageTick(int newtick);
		std::vector<LinePrimitive*> myLineBuffer;
		CLineMultiPrimitive* myLineMultiBuffer;
		int myNumberOfRenderedLines;
		int myMaxLines;
		CText* myFPS; 
		CText* myMemUsage;
		CText* myDrawCallText;
		CText* myCPUText;

		CSprite* myErrorSprite;
		
		
		int tickindex;
		int ticksum;
		int ticklist[MAXSAMPLES];
		float myShowErrorTimer;

		int myDebugFeatureSet;
		CPerformanceGraph *myPerformanceGraph;
		float myTimer;
		unsigned short myFPSCounter;
		unsigned short myRealFPS;
	};
}
