#pragma once


#include "../Vectors/vector2.h"


template<typename T>
class Line
{
public:     // Sets line to (0,0) -> (0,0) as this will produce most errors making sure the
	// user notices that the line isn't initialized properly.
	Line(void)
	{
		myPoint = CU::Point2<T>(0, 0);
		myDirection = CU::Vector2<T>(0, 0);
	}

	bool operator==(const Line & aLine)
	{
		return ((myPoint == aLine.myPoint) && (myDirection == aLine.myDirection));
	}

	bool operator!=(const Line & aLine)
	{
		return !((*this) == aLine);
	}

	// Initializes the line from two points
	//
	Line(const CU::Point2<T> &aFirstPoint, const CU::Point2<T> &aSecondPoint)
	{
		(*this).SetWith2Points(aFirstPoint, aSecondPoint);
	}

	// Sets the line data using two points
	//
	void SetWith2Points(const CU::Point2<T> &aFirstPoint, const CU::Point2<T> &aSecondPoint)
	{
		myPoint = aFirstPoint;
		myDirection = (aSecondPoint - aFirstPoint).GetNormalized();
	}

	// Sets the line data using a point and a direction
	//
	void SetWithPointAndDirection(const CU::Point2<T> &aPoint, const CU::Vector2<T> &aDirection)
	{
		myPoint = aPoint;
		myDirection = aDirection;
	}

	// Returns true if the point is on the inside of the line. The inside is defined as the
	// side opposite the normal. That is, the normal points to the outside of the line.
	//
	bool IsInside(const CU::Point2<T> &aPoint) const
	{
		if ((aPoint - myPoint).Dot(GetNormal()) <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Vector2<T> GetNormal(void) const
	{
		return CU::Vector2<T>(-myDirection.y, myDirection.x);
	}


private:    // Line representation goes here


	CU::Point2<T> myPoint;
	CU::Vector2<T> myDirection;
};
