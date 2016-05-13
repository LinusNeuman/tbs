#include "stdafx.h"
#include "NavGraph.h"
#include "../NavHandle.h"
#include "../Vertex/NavVertex.h"

NavGraph::NavGraph()
{
	myEdges.Init(1);
	myVertecies.Init(1);
}

NavGraph::~NavGraph()
{
}

VertexHandle NavGraph::AddVertex()
{
	VertexHandle handle = VertexHandle(myVertecies.Size(), this);
	myVertecies.Add(NavVertex(handle));
	return handle;
}

NavEdge* NavGraph::GetEdge(NavHandle aHandle)
{
	return &myEdges[aHandle];
}

NavVertex* NavGraph::GetVertex(NavHandle aHandle)
{
	return &myVertecies[aHandle];
}
