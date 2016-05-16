// Author:   Hampus Huledal
// CreationDate: 13/05/2016
#pragma once
#include "NavGraph//NavHandle.h"

class NavEdge
{
public:
	NavEdge();
	~NavEdge();

	void AddVertex(VertexHandle aVertex);
	VertexHandle GoThrough(VertexHandle aPreviousVertex) const;
	int GetCost()const;

private:
	VertexHandle myFirstVertex;
	VertexHandle mySecondVertex;
	int myCost;
};
