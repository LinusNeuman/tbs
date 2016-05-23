/*
*Author:  Hampus Huledal
*Date: 2016-05-13
*/
#pragma once
#include "NavGraph/Graph/NavGraph.h"


class NavEdge;
class NavVertex;

struct EdgeHandle
{
	NavHandle myHandle;

	EdgeHandle()
	{
		myHandle = 0;
		myGraph = nullptr;
	}

	EdgeHandle(NavHandle aHandle, NavGraph* aGraph)
	{
		myHandle = aHandle;
		myGraph = aGraph;
	}

	EdgeHandle& operator=(const NavHandle& aHandle)
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		myHandle = aHandle;
		return *this;
	}

	EdgeHandle operator+(const NavHandle& aHandle) const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return EdgeHandle(myHandle + aHandle, myGraph);
	}

	EdgeHandle& operator+=(const NavHandle& aHandle)
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		myHandle += aHandle;
		return *this;
	}

	EdgeHandle operator-(const NavHandle& aHandle) const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return EdgeHandle(myHandle - aHandle, myGraph);
	}

	EdgeHandle& operator-=(const NavHandle& aHandle)
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		myHandle -= aHandle;
		return *this;
	}

	EdgeHandle operator*(const NavHandle& aHandle) const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return EdgeHandle(myHandle * aHandle, myGraph);
	}

	EdgeHandle& operator*=(const NavHandle& aHandle)
	{ 
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		myHandle *= aHandle;
		return *this;
	}

	EdgeHandle operator/(const NavHandle& aHandle) const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return EdgeHandle(myHandle - aHandle, myGraph);
	}

	EdgeHandle& operator/=(const NavHandle& aHandle)
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		myHandle /= aHandle;
		return *this;
	}

	NavEdge* operator->() const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return myGraph->GetEdge(myHandle);
	}

	bool Null() const
	{
		return myGraph == nullptr;
	}

private:
	NavGraph * myGraph;
};

struct VertexHandle
{
	NavHandle myHandle;

	VertexHandle()
	{
		myHandle = 0;
		myGraph = nullptr;
	}

	VertexHandle(NavHandle aHandle, NavGraph* aGraph)
	{
		myHandle = aHandle;
		myGraph = aGraph;
	}

	bool operator==(const VertexHandle& aVertex) const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return myHandle == aVertex.myHandle && myGraph == aVertex.myGraph;
	}

	bool operator!=(const VertexHandle& aVertex)const
	{
		return ! (*this == aVertex);
	}

	VertexHandle& operator=(const NavHandle& aHandle)
	{
		myHandle = aHandle;
		return *this;
	}

	VertexHandle operator+(const NavHandle& aHandle) const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return VertexHandle(myHandle + aHandle, myGraph);
	}

	VertexHandle& operator+=(const NavHandle& aHandle)
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		myHandle += aHandle;
		return *this;
	}

	VertexHandle operator-(const NavHandle& aHandle) const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return VertexHandle(myHandle - aHandle, myGraph);
	}

	VertexHandle& operator-=(const NavHandle& aHandle)
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		myHandle -= aHandle;
		return *this;
	}

	VertexHandle operator*(const NavHandle& aHandle) const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return VertexHandle(myHandle * aHandle, myGraph);
	}

	VertexHandle& operator*=(const NavHandle& aHandle)
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		myHandle *= aHandle;
		return *this;
	}

	VertexHandle operator/(const NavHandle& aHandle) const
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		return VertexHandle(myHandle - aHandle, myGraph);
	}

	VertexHandle& operator/=(const NavHandle& aHandle)
	{
		DL_ASSERT(!Null(), "ERROR: Handle is not initialized!!")
		myHandle /= aHandle;
		return *this;
	}

	NavVertex* operator->() const
	{
		DL_ASSERT(!Null() , "ERROR: Handle is not initialized!!")
		return myGraph->GetVertex(myHandle);
	}

	bool Null() const
	{
		return myGraph == nullptr;
	}
private:
	NavGraph * myGraph;
};