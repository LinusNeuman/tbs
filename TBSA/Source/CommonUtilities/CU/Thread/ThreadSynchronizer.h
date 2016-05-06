#pragma once

#include <mutex>
#include <condition_variable>

class ThreadSynchronizer
{
public:
	ThreadSynchronizer();
	~ThreadSynchronizer();

	void Wait();
	void Notify();
private:
	std::mutex myMutex;
	std::condition_variable myConditionVariable;
	volatile bool myIsReady;

};

