// Author:   Hampus Huledal
// CreationDate: 13/05/2016
#pragma once

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

	void Clear();

	void Dijkstra(const VertexHandle& aFirstNode,const unsigned int aDistance);
private:
	CommonUtilities::GrowingArray<NavEdge, NavHandle> myEdges;
	CommonUtilities::GrowingArray<NavVertex, NavHandle> myVertecies;
};
