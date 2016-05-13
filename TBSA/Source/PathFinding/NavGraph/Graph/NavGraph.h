// Author:   Hampus Huledal
// CreationDate: 13/05/2016
#pragma once
#include <CU/GrowingArray/GrowingArray.h>

struct NavVertex;
struct NavEdge;

typedef unsigned int NavHandle;
class  VertexHandle;

class NavGraph
{
public:
	NavGraph();
	~NavGraph();
	
	
	VertexHandle AddVertex();

	NavEdge* GetEdge(NavHandle aHandle);
	NavVertex* GetVertex(NavHandle aHandle);
private:
	CommonUtilities::GrowingArray<NavEdge, NavHandle> myEdges;
	CommonUtilities::GrowingArray<NavVertex, NavHandle> myVertecies;
};
