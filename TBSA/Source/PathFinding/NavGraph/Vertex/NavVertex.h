// Author:   Hampus Huledal
// CreationDate: 13/05/2016
#pragma once
#include "NavGraph/NavHandle.h"
#include "NavGraph/Edge/NavEdge.h"

class NavVertex
{
public:
	NavVertex();
	NavVertex(VertexHandle aHandle);
	~NavVertex();

	bool IsSearched() const;
	void SetIfSearched(bool aState);

	void SetDistance(const unsigned int aDisctance, const bool aShallCompare = true);
	unsigned int GetDistance() const;

	void SetAnyPurpouseId(int anID);
	int GetAnyPurpouseId() const;

	void SetPreviousNode(VertexHandle aPreviousVertex);

	void AddLink(EdgeHandle anEdge, VertexHandle aVertex);

	const CommonUtilities::GrowingArray<EdgeHandle>& GetEdges() const;

private:
	void AddEdge(const EdgeHandle& anEdge);
	CommonUtilities::GrowingArray<EdgeHandle> myEdges;

	VertexHandle myPrevoiusNode;
	VertexHandle myHandle;

	bool myIsSearched;
	unsigned int myDistance;
	int myAnyPurpouseId;
};

inline bool NavVertex::IsSearched() const
{
	return myIsSearched;
}

inline unsigned NavVertex::GetDistance() const
{
	return myDistance;
}

inline void NavVertex::SetDistance(const unsigned aDisctance, const bool aShallCompare)
{
	if (aShallCompare == false || aDisctance < myDistance)
	{
		myDistance = aDisctance;
	}
}

inline void NavVertex::SetIfSearched(bool aState)
{
	myIsSearched = aState;
}
