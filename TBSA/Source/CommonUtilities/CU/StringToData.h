#pragma once
#include "CU/Vectors/Vector.h"
#include <string>
#include "CU/DLDebug/DL_Debug.h"
#include "CU/NameSpaceAliases.h"

namespace StringToData
{
	inline CU::Vector2f StringToVector2f(const std::string& aVectorString)
	{
		DL_ASSERT(aVectorString.size() != 0, "Invalid vector input in cutscene!");

		std::string part;
		int numberOfParameters = 0;
		float pos[2];

		for (size_t i = 0; i < aVectorString.size(); ++i)
		{
			if (aVectorString[i] == ',')
			{
				pos[numberOfParameters] = std::stof(part);

				part = "";

				++numberOfParameters;
			}
			else
			{
				part += aVectorString[i];
			}
		}
		pos[numberOfParameters] = std::stof(part);
		++numberOfParameters;

		DL_ASSERT(numberOfParameters == 2, "Unexpected numer of parameters to vector in cutscene, expected 2, got " + numberOfParameters);

		return CU::Vector2f(pos[0], pos[1]);
	}

	inline CU::Vector4f StringToVector4f(const std::string& aVectorString)
	{
		DL_ASSERT(aVectorString.size() != 0, "Invalid vector input in cutscene!");

		std::string part;
		int numberOfParameters = 0;
		float pos[4];

		for (size_t i = 0; i < aVectorString.size(); ++i)
		{
			if (aVectorString[i] == ',')
			{
				pos[numberOfParameters] = std::stof(part);

				part = "";

				++numberOfParameters;
			}
			else
			{
				part += aVectorString[i];
			}
		}
		pos[numberOfParameters] = std::stof(part);
		++numberOfParameters;

		DL_ASSERT(numberOfParameters == 4, "Unexpected numer of parameters to vector in cutscene, expected 2, got " + numberOfParameters);

		return CU::Vector4f(pos[0], pos[1], pos[2], pos[3]);
	}
}
