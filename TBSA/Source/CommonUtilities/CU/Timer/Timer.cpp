#include "stdafx.h"
#include "Timer.h"
#include "TimeManager.h"
#include "../DLDebug/DL_Debug.h"

namespace CommonUtilities
{
	Timer::Timer() : myTime(0)
	{
		myTimeStamp = TimeManager::GetMainStamp();

		myPauseStamp = myTimeStamp;
		myImPaused = false;
	}


	Timer::~Timer()
	{
	}

	void Timer::PauseTimer()
	{
		if (myImPaused == false)
		{
			myImPaused = true;
			myPauseStamp = TimeManager::GetMainStamp();
		}
	}

	void Timer::UnpauseTimer()
	{
		if (myImPaused == true)
		{
			myImPaused = false;
			myTimeStamp += (TimeManager::GetMainStamp() - myPauseStamp);
		}
	}

	const Time & Timer::GetTime()
	{
		if (myImPaused == false)
		{
			SetTime(TimeManager::GetMainStamp() - myTimeStamp);
		}
		else
		{
			SetTime(myPauseStamp - myTimeStamp);
		}

		return myTime;
	}

	void Timer::SetTime(LONGLONG aTimeStamp)
	{
		myTime.SetTime(aTimeStamp);
	}

	void Timer::Reset()
	{
		myTimeStamp = TimeManager::GetMainStamp();
	}
}