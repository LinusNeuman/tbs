#include "stdafx.h"
#include "ThreadSynchronizer.h"


ThreadSynchronizer::ThreadSynchronizer()
{
}


ThreadSynchronizer::~ThreadSynchronizer()
{
}


void ThreadSynchronizer::Wait()
{
	std::unique_lock<std::mutex> lock (myMutex);
	myConditionVariable.wait(lock, [=]{return myIsReady == true; });
	myIsReady = false;
	lock.unlock();
}

void ThreadSynchronizer::Notify()
{
	myMutex.lock();
	if (myIsReady == true)
	{
		myMutex.unlock();
		return;
	}
	myIsReady = true;
	myMutex.unlock();
	myConditionVariable.notify_all();
}