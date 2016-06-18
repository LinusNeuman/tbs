#include "stdafx.h"
#include "NavGraph.h"
#include "NavGraph/NavHandle.h"
#include "NavGraph/Vertex/NavVertex.h"
#include "NavGraph/Edge/NavEdge.h"
#include <CU/Heap/Heap.h>
#include <NavGraph/Comparers/VertexLesser.h>


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

	// Här borde den väl kolla om first node är null och i så fall returna?
	// Annars kraschar den ju.
	// - Findus 18/06

	aFirstNode->SetDistance(0);
	if (aDistance == 0)
	{
		aFirstNode->SetIfSearched(true);
		return;
	}

	

	CommonUtilities::Heap<VertexHandle, CommonUtilities::VertexLesser>openNodes;
	openNodes.Enqueue(aFirstNode);

	while (openNodes.IsEmpty() == false)
	{
		if (openNodes.IsHeap() == false)
		{
			openNodes.Resort();
		}
		VertexHandle currentNode = openNodes.Dequeue();
		
		currentNode->SetIfSearched(true);
		currentNode->SetIfOpen(false);

		CommonUtilities::GrowingArray<EdgeHandle> currentEdges = currentNode->GetEdges();
		
		for (size_t j = 0; j < currentEdges.Size(); j++)
		{
			VertexHandle currentNeighbor = currentEdges[j]->GoThrough(currentNode);
			if (currentNeighbor->IsSearched() == true)
			{
				continue;
			}

			const float cost = currentEdges[j]->GetCost();
			if (currentNeighbor->GetDistance() > currentNode->GetDistance() + cost)
			{
				currentNeighbor->SetDistance(currentNode->GetDistance() + cost);
				currentNeighbor->SetPreviousNode(currentNode);
			}

			if (currentNeighbor->GetIfOpen() == false && currentNeighbor->GetDistance() < aDistance)
			{
				currentNeighbor->SetIfOpen(true);
				openNodes.Enqueue(currentNeighbor);
			}
			else if (currentNeighbor->GetDistance() >= aDistance)
			{
				currentNeighbor->SetIfSearched(true);
			}
		}
	}
}
