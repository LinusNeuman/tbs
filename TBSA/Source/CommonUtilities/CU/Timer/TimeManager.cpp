#include "stdafx.h"
#include "TimeManager.h"


namespace CommonUtilities
{

	TimeManager * TimeManager::ourInstance;

	void TimeManager::Create()
	{
		if (ourInstance == nullptr)
		{
			ourInstance = new TimeManager();
		}
	}

	void TimeManager::Destroy()
	{
		delete ourInstance;
		ourInstance = nullptr;
	}


	void TimeManager::Update()
	{
		GetInstance().DoUpdate();
	}


	void TimeManager::DoUpdate()
	{
		if (myImPaused == false)
		{
			QueryPerformanceCounter(&myCurrentStamp);
			myTimeDifference.QuadPart = static_cast<LONGLONG>((myCurrentStamp.QuadPart - myCountFromStamp.QuadPart) / (myFrequency));
			myDeltaTime = static_cast<LONGLONG>((myCurrentStamp.QuadPart - myPreviousStamp.QuadPart) / (myFrequency));

			myPreviousStamp = myCurrentStamp;
		}
	}

	 Time TimeManager::GetDeltaTime()
	{
		/*if (GetInstance().myDeltaTime / 1000000.0 >= 1)
		{
			return Time(0);
		}*/
		return Time(GetInstance().myDeltaTime);
	}

	/*size_t TimeManager::CreateNewTimer()
	{
		GetInstance().myTimers.push_back(Timer(GetInstance().myTimeDifference.QuadPart));
		return GetInstance().myTimers.size() - 1;
	}*/

	LONGLONG TimeManager::GetTimeSinceStart()
	{
		return  static_cast<LONGLONG>((static_cast<double>(GetInstance().myTimeDifference.QuadPart) / 1000000.0));
	}

	LONGLONG TimeManager::GetMainStamp()
	{
		return GetInstance().myTimeDifference.QuadPart;
	}

	/*Timer & TimeManager::GetTimer(size_t aTimerIndex)
	{
		return GetInstance().myTimers[aTimerIndex];
	}*/

	const Time & TimeManager::GetTimerTime(size_t aTimerIndex)
	{
		return GetInstance().myTimers[aTimerIndex].GetTime();
	}

	void TimeManager::PauseAllTimers()
	{
		GetInstance().DoPauseAllTimers();
	}

	void TimeManager::ResumeAllTimers()
	{
		GetInstance().DoResumeAllTimers();
	}
	

	void TimeManager::DoPauseAllTimers()
	{
		if (myImPaused == false)
		{
			myImPaused = true;
			QueryPerformanceCounter(&myPauseStamp);
		}
	}

	void TimeManager::DoResumeAllTimers()
	{
		if (myImPaused == true)
		{
			myImPaused = false;
			LARGE_INTEGER tempCounter;
			QueryPerformanceCounter(&tempCounter);
			myCountFromStamp.QuadPart = myCountFromStamp.QuadPart + (tempCounter.QuadPart + myPauseStamp.QuadPart);
		}
	}



	TimeManager::TimeManager()
	{
		LARGE_INTEGER tempGetFrequency;
		QueryPerformanceFrequency(&tempGetFrequency);
		QueryPerformanceCounter(&myStartStamp);
		myPreviousStamp = myStartStamp;
		myCurrentStamp = myStartStamp;
		myCountFromStamp = myStartStamp;

		myImPaused = false;

		myFrequency = static_cast<double>(tempGetFrequency.QuadPart) / 1000000.0;
	}


	TimeManager::~TimeManager()
	{
	}

}
