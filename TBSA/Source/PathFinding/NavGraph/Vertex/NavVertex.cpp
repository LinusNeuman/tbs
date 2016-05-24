#include "stdafx.h"
#include "NavVertex.h"
#include "NavGraph/Edge/NavEdge.h"


NavVertex::NavVertex()
{
	DL_PRINT("WARNING: created a null handle!!!!")
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

void NavVertex::SetAnyPurpouseId(int anID)
{
	myAnyPurpouseId = anID;
}

int NavVertex::GetAnyPurpouseId() const
{
	return myAnyPurpouseId;
}

void NavVertex::SetPreviousNode(VertexHandle aPreviousVertex)
{
	myPrevoiusNode = aPreviousVertex;
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
