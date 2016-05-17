#pragma once

namespace CommonUtilities
{

	template<typename T>
	class PointerGreater
	{
	public:
		bool operator()(const T & aShouldBeLarger, const T & aShouldBeLesser);
	};

	template<typename T>
	bool CommonUtilities::PointerGreater<T>::operator()(const T & aShouldBeLarger, const T & aShouldBeLesser)
	{
		return (*aShouldBeLarger > *aShouldBeLesser);
	}
}