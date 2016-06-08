#pragma once

#include <vector>
#include <queue>
#include "Workplace/Worker.h"
#include "Workplace/Work.h"
#include <thread>

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void AddWork(const Work& someWork);
	void Update();
private:
	std::vector<Worker> myWorkers;
	std::queue<Work> myWork;
};

