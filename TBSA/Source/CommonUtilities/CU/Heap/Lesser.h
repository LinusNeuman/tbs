#pragma once

namespace CommonUtilities
{

	template<typename T>
	class Lesser
	{
	public:
		bool operator()(const T & aShouldBeLesser, const T & aShouldBeLarger);
	};

	template<typename T>
	bool CommonUtilities::Lesser<T>::operator()(const T & aShouldBeLesser, const T & aShouldBeLarger)
	{
		return (aShouldBeLarger > aShouldBeLesser);
	}
}