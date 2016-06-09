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
	float GetCost()const;
	void Setcost(const float);

private:
	VertexHandle myFirstVertex;
	VertexHandle mySecondVertex;
	float myCost;
};
