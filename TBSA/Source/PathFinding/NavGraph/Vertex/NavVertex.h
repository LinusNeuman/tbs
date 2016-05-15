// Author:   Hampus Huledal
// CreationDate: 13/05/2016
#pragma once
#include "NavGraph/NavHandle.h"
#include <CU/GrowingArray/GrowingArray.h>
#include "NavGraph/Edge/NavEdge.h"

class NavVertex
{
public:
	NavVertex();
	NavVertex(VertexHandle aHandle);
	~NavVertex();

	
	void AddLink(EdgeHandle anEdge, VertexHandle aVertex);
	const CommonUtilities::GrowingArray<EdgeHandle>& GetEdges() const;
private:
	void AddEdge(const EdgeHandle& anEdge);
	CommonUtilities::GrowingArray<EdgeHandle> myEdges;
	VertexHandle myHandle;
};
