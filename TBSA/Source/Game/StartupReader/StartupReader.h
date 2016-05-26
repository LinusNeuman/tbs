#pragma once

class JsonWrapper;
struct StartupData;

class StartupReader
{
public:
	StartupReader();
	~StartupReader();

	StartupData LoadAndGetStartupData();

private:
	JsonWrapper * myJsonWrapper;
};