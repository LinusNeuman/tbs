#include "Worker.h"
#include <thread>


Worker::Worker()
{
	myIsWorking = false;
	myStop = false;
	myThread = nullptr;
}

Worker::~Worker()
{
	if (myThread != nullptr)
	{
		if (myThread->joinable() == true)
		{
			myThread->join();
		}
		
	}
	delete myThread;
}

void Worker::AssignWork(Work someWork)
{
	myWork = someWork;
	myIsWorking = true;
	
	if (myThread == nullptr)
	{
		myThread = new std::thread(&Worker::Update, this);
	}
}

void Worker::Update()
{	
	while (myStop == false)
	{
		if (myIsWorking == false)
		{
			std::this_thread::yield();
		}
		else
		{
			myWork.DoWork();
			myIsWorking = false;
		}
	}
}
