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

	void SetDistance(const float aDisctance, const bool aShallCompare = true);
	float GetDistance() const;

	void SetAnyPurpouseId(int anID);
	int GetAnyPurpouseId() const;

	void SetPreviousNode(VertexHandle aPreviousVertex);

	void AddLink(EdgeHandle anEdge, VertexHandle aVertex);

	const CommonUtilities::GrowingArray<EdgeHandle>& GetEdges() const;

	CommonUtilities::GrowingArray<int> GetPath() const;

	bool GetIfOpen() const;
	void SetIfOpen(const bool);
private:
	void AddEdge(const EdgeHandle& anEdge);
	CommonUtilities::GrowingArray<EdgeHandle> myEdges;

	void InternalGetPath(CommonUtilities::GrowingArray<int> & aPath) const;

	VertexHandle myPrevoiusNode;
	VertexHandle myHandle;

	bool myIsOpen;
	bool myIsSearched;
	float myDistance;
	int myAnyPurpouseId;
};

inline bool NavVertex::IsSearched() const
{
	return myIsSearched;
}

inline float NavVertex::GetDistance() const
{
	return myDistance;
}

inline void NavVertex::SetDistance(float aDisctance, const bool aShallCompare)
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

inline bool NavVertex::GetIfOpen() const
{
	return myIsOpen;
}

inline void NavVertex::SetIfOpen(const bool aState)
{
	myIsOpen = aState;
}
