#include "ThreadPool.h"
#include <iostream>
#include <string>

ThreadPool::ThreadPool()
{
	unsigned char hardwareThreads = std::thread::hardware_concurrency();

	if (hardwareThreads > 0)
	{
		for (unsigned char i = 0; i < hardwareThreads; ++i)
		{
			myWorkers.emplace_back();
		}
	}
}

void ThreadPool::AddWork(const Work& someWork)
{
	myWork.push(someWork);
}

void ThreadPool::Update()
{
	while (myWork.size() > 0)
	{
		for (unsigned char ch = 0; ch < myWorkers.size(); ++ch)
		{
			if (myWorkers[ch].GetIsWorking() == false)
			{
				myWorkers[ch].AssignWork(myWork.front());
				myWork.pop();
			}
			if (myWork.size() == 0)
			{
				break;
			}
		}
	}
}

ThreadPool::~ThreadPool()
{
}
