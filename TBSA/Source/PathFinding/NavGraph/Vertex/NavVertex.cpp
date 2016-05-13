#include "stdafx.h"
#include "NavVertex.h"
#include "../Edge/NavEdge.h"


NavVertex::NavVertex()
{
	//dangerous
}

NavVertex::NavVertex(VertexHandle aHandle) : myHandle(aHandle)
{
}

NavVertex::~NavVertex()
{
}

void NavVertex::AddEdge(const EdgeHandle& anEdge)
{
	anEdge->AddVertex(myHandle);
	myEdges.Add(anEdge);
}

void NavVertex::AddLink(EdgeHandle anEdge, VertexHandle aVertex)
{
	aVertex->AddEdge(anEdge);
	AddEdge(anEdge);
}

const CommonUtilities::GrowingArray<EdgeHandle>& NavVertex::GetEdges() const
{
	return myEdges;
}
