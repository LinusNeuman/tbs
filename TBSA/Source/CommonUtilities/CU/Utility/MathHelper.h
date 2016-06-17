#pragma once
#include <cstdlib>

namespace CommonUtilities
{
	namespace Math
	{
		int CapValue(int aMinValue, int aMaxValue, int aValueToCap)
		{
			if (aValueToCap > aMaxValue)
			{
				aValueToCap = aMaxValue;
			}
			else if (aValueToCap < aMinValue)
			{
				aValueToCap = aMinValue;
			}

			return aValueToCap;
		}

		float CapValue(const float aMinValue, const float aMaxValue, float aValueToCap)
		{
			if (aValueToCap > aMaxValue)
			{
				aValueToCap = aMaxValue;
			}
			else if (aValueToCap < aMinValue)
			{
				aValueToCap = aMinValue;
			}

			return aValueToCap;
		}

		float Saturate(const float aValue)
		{
			return CapValue(0.f, 1.f, aValue);
		}

		template <typename T>
		T RandomRange(const T aMinValue, const T aMaxValue)
		{
			float alpha = static_cast<float>(rand() % 10000) / 10000.f;
			return Lerp<T>(aMinValue, aMaxValue, alpha);
		}

		template <typename T>
		T Lerp(const T aStartValue, const T aEndValue, float aAlpha)
		{
			aAlpha = Saturate(aAlpha);
			return static_cast<T>(aStartValue + (aEndValue - aStartValue) * aAlpha);
		}
	}
}
namespace CU = CommonUtilities;
