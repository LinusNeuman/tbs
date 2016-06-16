#include "stdafx.h"
#include "Time.h"

namespace CommonUtilities
{

	Time::Time(LONGLONG aTime)
	{
		myTimeInMicroSeconds = aTime;
	}


	Time::~Time()
	{
	}



	LONGLONG Time::GetMicroSeconds() const
	{
		return myTimeInMicroSeconds;
	}

	float Time::GetMilliSeconds() const
	{
		return (static_cast<float>(myTimeInMicroSeconds) / 1000.f);
	}

	float Time::GetMinutes() const
	{
		return (GetSeconds() / 60.f);
	}

	float Time::GetHours() const
	{
		return (GetMinutes() / 60.f);
	}

	float Time::GetSeconds() const
	{
		return (static_cast<float>(myTimeInMicroSeconds) / 1000000.f);
	}

	void Time::SetTime(LONGLONG aTime)
	{
		myTimeInMicroSeconds = aTime;
	}

}
