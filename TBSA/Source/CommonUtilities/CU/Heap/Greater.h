#pragma once

namespace CommonUtilities
{

	template<typename T>
	class Greater
	{
	public:
		bool operator()(const T & aShouldBeLarger, const T & aShouldBeLesser);
	};

	template<typename T>
	bool CommonUtilities::Greater<T>::operator()(const T & aShouldBeLarger, const T & aShouldBeLesser)
	{
		return (aShouldBeLarger > aShouldBeLesser);
	}
}