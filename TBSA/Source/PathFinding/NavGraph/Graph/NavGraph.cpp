#include "stdafx.h"
#include "NavGraph.h"
#include "NavGraph/NavHandle.h"
#include "NavGraph/Vertex/NavVertex.h"

NavGraph::NavGraph()
{
	myEdges.Init(1);
	myVertecies.Init(1);
}

NavGraph::~NavGraph()
{
}

VertexHandle NavGraph::CreateVertex()
{
	VertexHandle handle = VertexHandle(myVertecies.Size(), this);
	myVertecies.Add(NavVertex(handle));
	return handle;
}

EdgeHandle NavGraph::CreateEdge()
{
	EdgeHandle handle = EdgeHandle(myEdges.Size(), this);
	myEdges.Add(NavEdge());
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
