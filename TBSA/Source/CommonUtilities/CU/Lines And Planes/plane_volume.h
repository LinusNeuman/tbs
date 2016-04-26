#pragma once


#include "plane.h"
#include "../GrowingArray/GrowingArray.h"


template<typename T>
class PlaneVolume
{
public:     // Initializes the volume with a list of planes.
			//
			PlaneVolume()
			{
				myArray.Init(1);
			}

			PlaneVolume(const CommonUtilities::GrowingArray<Plane<T>> &somePlanes)
			{
				myArray = somePlanes;
			}

			// Adds a plane to the volume
			//
			void AddPlane(const Plane<T> &aPlane)
			{
				myArray.Add(aPlane);
			}

			// Removes a plane from the volume.
			//
			void RemovePlane(const Plane<T> &aPlane)
			{
				myArray.RemoveCyclic(aPlane);
			}

			// Returns true if the point is inside of all planes in the volume.
			//
			bool Inside(const Point3<T> &aPoint) const
			{
				for (size_t iPlane = 0; iPlane < myArray.Size(); ++iPlane)
				{
					if (myArray[iPlane].IsInside(aPoint) == false)
					{
						return false;
					}
				}

				return true;
			}

private:    // Internal representation of the plane goes here
	
	CommonUtilities::GrowingArray<Plane<T>> myArray;
};
