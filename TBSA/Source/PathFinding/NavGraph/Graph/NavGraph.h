// Author:   Hampus Huledal
// CreationDate: 13/05/2016
#pragma once

class NavVertex;
class NavEdge;

typedef unsigned int NavHandle;
struct  VertexHandle;

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
