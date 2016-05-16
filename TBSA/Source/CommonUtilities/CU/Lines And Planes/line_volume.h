#pragma once


#include "line.h"
#include "CU/GrowingArray/GrowingArray.h"


template<typename T>
class LineVolume
{
public:     // Initializes the volume with a list of lines.
			//
			LineVolume(const CommonUtilities::GrowingArray<Line<T>> &someLines)
			{
				myArray = someLines;
			}

			// Adds a line to the volume
			//
			void AddLine(const Line<T> &aLine)
			{
				myArray.Add(aLine);
			}

			// Removes a line from the volume.
			//
			void RemoveLine(const Line<T> &aLine)
			{
				myArray.RemoveCyclic(aLine);
			}

			// Returns true if the point is inside of all lines in the volume.
			//
			bool Inside(const Point2<T> &aPoint) const
			{
				for (size_t iLine = 0; iLine < myArray.Size(); ++iLine)
				{
					if (myArray[iLine].IsInside(aPoint) == false)
					{
						return false;
					}
				}

				return true;
			}

private:    // Internal representation of the line goes here
	CommonUtilities::GrowingArray<Line<T>> myArray;
};
