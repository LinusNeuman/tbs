#include "stdafx.h"
#include "NavGraph.h"
#include "NavGraph/NavHandle.h"
#include "NavGraph/Vertex/NavVertex.h"
#include "NavGraph/Edge/NavEdge.h"
#include <CU/Heap/Heap.h>
#include <map>


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

void NavGraph::Dijkstra(VertexHandle& aFirstNode, unsigned aDistance)
{
	for (size_t i = 0; i < myVertecies.Size(); ++i)
	{
		myVertecies[i].SetDistance(INT_MAX);
	}

	aFirstNode->SetDistance(0);

	std::map<NavHandle, VertexHandle> openNodes;
	openNodes[aFirstNode.myHandle] = aFirstNode;

	while (openNodes.empty() == false)
	{
		VertexHandle currentNode = openNodes.begin()->second;
		openNodes.erase(currentNode.myHandle);
		currentNode->SetIfSearched(true);

		CommonUtilities::GrowingArray<EdgeHandle> currentEdges = currentNode->GetEdges();
		
		for (size_t j = 0; j < currentEdges.Size(); j++)
		{
			//VertexHandle currentNeighbor = currentEdges->
		}
	}
}