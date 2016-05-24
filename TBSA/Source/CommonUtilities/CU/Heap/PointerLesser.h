#pragma once

namespace CommonUtilities
{

	template<typename T>
	class PointerLesser
	{
	public:
		bool operator()(const T & aShouldBeLesser, const T & aShouldBeLarger);
	};

	template<typename T>
	bool CommonUtilities::PointerLesser<T>::operator()(const T & aShouldBeLesser, const T & aShouldBeLarger)
	{
		return (*aShouldBeLarger > *aShouldBeLesser);
	}
}