#include "stdafx.h"
#include "Alarm.h"
#include "TimeManager.h"


namespace CommonUtilities
{
	Alarm::Alarm()
	{
		myTimeToCheck = -1.f;
		myIShouldReset = false;
		myRemainingTime = 0.f;
	}

	Alarm::Alarm(const float aTimeToCheck, const bool aShouldResetWhenDone)
	{
		myTimeToCheck = aTimeToCheck;

		myIShouldReset = aShouldResetWhenDone;
	}


	Alarm::~Alarm()
	{
	}


	void Alarm::SetAlarmTimeLength(const float aTimeToCheck)
	{
		myTimeToCheck = aTimeToCheck;
	}

	float Alarm::GetProgress()
	{
		DL_ASSERT(myTimeToCheck > 0.f, "TimeToCheck on a alarm is not above 0");

		//const float tesTime = myTimer.GetTime().GetSeconds();

		const float CurrentProgress = (myTimer.GetTime().GetSeconds() + myRemainingTime) / myTimeToCheck;
		

		if (CurrentProgress >= 1.f)
		{
			if (myIShouldReset)
			{
				myRemainingTime = ((myTimer.GetTime().GetSeconds() + myRemainingTime) - myTimeToCheck);
				myTimer.Reset();
			}

			return 1.f;
		}
		else
		{
			return CurrentProgress;
		}
	}

	float Alarm::GetReverseProgress()
	{
		return 1.f - GetProgress();
	}

	void Alarm::Reset()
	{
		myRemainingTime = 0.f;
		myTimer.Reset();
	}

	void Alarm::SetResetBool(const bool aShouldResetWhenDone)
	{
		myIShouldReset = aShouldResetWhenDone;
	}
}