#pragma once

#include "Work.h"
#include <thread>
#include <mutex>
#include <atomic>

class Worker
{
public:
	Worker();
	~Worker();
	
	void AssignWork(Work someWork);
	bool GetIsWorking() { return myIsWorking; };
private:
	void Update();
	volatile bool myIsWorking;
	Work myWork;
	std::thread* myThread;
	bool myStop;
};

