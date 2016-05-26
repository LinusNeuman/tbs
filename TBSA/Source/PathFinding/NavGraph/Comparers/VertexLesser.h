#pragma once
/*
*Author:  Hampus Huledal
*Date: 25-05-2016
*/
#include "../Vertex/NavVertex.h"
#include "../NavHandle.h"

namespace CommonUtilities
{

	class VertexLesser
	{
	public:
		bool operator()(const VertexHandle & aShouldBeLesser, const VertexHandle & aShouldBeLarger) const;
	};


	inline bool CommonUtilities::VertexLesser::operator()(const VertexHandle & aShouldBeLesser, const VertexHandle & aShouldBeLarger) const
	{
		return (aShouldBeLarger->GetDistance() > aShouldBeLesser->GetDistance());
	}
}