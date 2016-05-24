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

void NavGraph::Clear()
{
	for (size_t i = 0; i < myVertecies.Size(); ++i)
	{
		myVertecies[i].SetDistance(10000 * 10000, false);
		myVertecies[i].SetIfSearched(false);
		myVertecies[i].SetPreviousNode(VertexHandle());
	}
}

void NavGraph::Dijkstra(const VertexHandle& aFirstNode,const unsigned aDistance)
{
	Clear();

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
			VertexHandle currentNeighbor = currentEdges[j]->GoThrough(currentNode);
			if (currentNeighbor->IsSearched() == true)
			{
				continue;
			}

			const int cost = currentEdges[j]->GetCost();
			if (currentNeighbor->GetDistance() > currentNode->GetDistance() + cost)
			{
				currentNeighbor->SetDistance(currentNode->GetDistance() + cost);
				currentNeighbor->SetPreviousNode(currentNode);
			}

			if (openNodes.count(currentNeighbor.myHandle) == 0 && currentNeighbor->GetDistance() < aDistance)
			{
				openNodes[currentNeighbor.myHandle] = currentNeighbor;
			}
			else if (currentNeighbor->GetDistance() >= aDistance)
			{
				currentNeighbor->SetIfSearched(true);
			}
		}
	}
}
