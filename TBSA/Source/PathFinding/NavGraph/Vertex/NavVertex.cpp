#include "stdafx.h"
#include "NavVertex.h"
#include "NavGraph/Edge/NavEdge.h"


NavVertex::NavVertex()
{
	DL_PRINT("WARNING: created a null handle!!!!");
		//dangerous
	myEdges.Init(1);
}

NavVertex::NavVertex(VertexHandle aHandle) : myHandle(aHandle)
{
	myEdges.Init(1);
}

NavVertex::~NavVertex()
{
}

void NavVertex::AddEdge(const EdgeHandle& anEdge)
{
	anEdge->AddVertex(myHandle);
	myEdges.Add(anEdge);
}

void NavVertex::InternalGetPath(CommonUtilities::GrowingArray<int>& aPath) const
{
	aPath.Add(myAnyPurpouseId);
	if (myPrevoiusNode.Null() != true)
	{
		myPrevoiusNode->InternalGetPath(aPath);
	}
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

CommonUtilities::GrowingArray<int> NavVertex::GetPath() const
{
	CommonUtilities::GrowingArray<int> path;
	path.Init(1);
	InternalGetPath(path);
	return path;
}
