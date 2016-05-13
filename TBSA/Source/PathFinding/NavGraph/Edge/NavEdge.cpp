#include "stdafx.h"
#include "NavEdge.h"

NavEdge::NavEdge() : myFirstVertex(0, nullptr), mySecondVertex(0, nullptr)
{
	myCost = 1;
}

NavEdge::~NavEdge()
{
}

void NavEdge::AddVertex(VertexHandle aVertex)
{
	if (myFirstVertex.Null())
	{
		myFirstVertex = aVertex;
	}
	else if (mySecondVertex.Null())
	{
		mySecondVertex = aVertex;
	}
	else
	{
		DL_ASSERT(false, "ERROR Edge can't link to more than one vertex")
	}
}

VertexHandle NavEdge::GoThrough(VertexHandle aPreviousVertex) const
{
	DL_ASSERT(!(myFirstVertex.Null() || mySecondVertex.Null()), "Error: Edge not fully linked")
	DL_ASSERT(myFirstVertex == aPreviousVertex || mySecondVertex == aPreviousVertex, "Error: edge does not link to that vertex")
	if (aPreviousVertex == myFirstVertex)
	{
		return  mySecondVertex;
	}
	else 
	{
		return  myFirstVertex;
	}
	
}

int NavEdge::GetCost() const
{
	return myCost;
}
