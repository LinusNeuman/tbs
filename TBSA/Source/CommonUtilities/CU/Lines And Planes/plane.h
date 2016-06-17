#pragma once


#include "CU/Vectors/vector3.h"



template<typename T>
class Plane
{
public:     // Sets all plane values to 0 to make it obvious to the user that it's not initialized.
			//
			Plane(void)
			{	
				myPoint = CU::Point3<T>(0, 0, 0);
				myNormal = CU::Vector3<T>(0, 0, 0);
			}

			// Initializes the plane using three points
			//
			Plane(const CU::Point3<T> &aFirstPoint, const CU::Point3<T> &aSecondPoint, const CU::Point3<T> &aThirdPoint)
			{
				SetWith3Points(aFirstPoint, aSecondPoint, aThirdPoint);
			}

			// Initializes the plane using a point and a normal
			//
			Plane(const CU::Point3<T> &aPoint, const CU::Vector3<T> &aNormal)
			{
				SetWithPointAndNormal(aPoint, aNormal);
			}

			bool operator==(const Plane & aPlane)
			{
				return ((myPoint == aPlane.myPoint) && (myNormal == aPlane.myNormal));
			}

			bool operator!=(const Plane & aPlane)
			{
				return !((*this) == aPlane);
			}

			// Sets the plane from three points
			//
			void SetWith3Points(const CU::Point3<T> &aFirstPoint, const CU::Point3<T> &aSecondPoint, const CU::Point3<T> &aThirdPoint)
			{
				CU::Vector3<T> firstVector = aThirdPoint - aFirstPoint;
				CU::Vector3<T> secondVector = aSecondPoint - aFirstPoint;

				myNormal = firstVector.Cross(secondVector).Normalize();
			}

			// Sets the plane from a point and a normal
			//
			void SetWithPointAndNormal(const CU::Point3<T> &aPoint, const CU::Vector3<T> &aNormal)
			{
				myNormal = aNormal;
				myPoint = aPoint;
			}

			// Returns true if the point is on the inside of the plane. The inside is defined as
			// the opposite side of where the normal points to.
			//
			bool IsInside(const CU::Point3<T> &aPoint) const
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

			const CU::Vector3<T> & GetNormal(void) const
			{
				return myNormal;
			}

			T GetSelfProjection() const
			{
				return myPoint.Dot(myNormal);
			}

private:    // Plane representation goes here
	CU::Point3<T> myPoint;
	CU::Vector3<T> myNormal;
};
