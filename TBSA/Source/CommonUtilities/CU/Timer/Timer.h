#pragma once
#include "Time.h"

namespace CommonUtilities
{

	class Timer
	{
	public:
		Timer();
		~Timer();

		void PauseTimer();

		void UnpauseTimer();

		//void Update(LONGLONG aTimeStamp);

		const Time & GetTime();

		void SetTimerCheckValue(const float aTimeInSeconds);

		void Reset();

	private:
		void SetTime(LONGLONG aTimeStamp);

		LONGLONG myTimeStamp;
		LONGLONG myPauseStamp;

		Time myTime;

		bool myImPaused;
	};
}