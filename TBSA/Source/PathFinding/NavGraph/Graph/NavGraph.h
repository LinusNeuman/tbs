// Author:   Hampus Huledal
// CreationDate: 13/05/2016
#pragma once
#include <CU/GrowingArray/GrowingArray.h>

class NavVertex;
class NavEdge;

typedef unsigned int NavHandle;
struct VertexHandle;
struct EdgeHandle;

class NavGraph
{
public:
	NavGraph();
	~NavGraph();
	
	VertexHandle CreateVertex();
	EdgeHandle CreateEdge();

	NavEdge* GetEdge(NavHandle aHandle);
	NavVertex* GetVertex(NavHandle aHandle);
private:
	CommonUtilities::GrowingArray<NavEdge, NavHandle> myEdges;
	CommonUtilities::GrowingArray<NavVertex, NavHandle> myVertecies;
};
