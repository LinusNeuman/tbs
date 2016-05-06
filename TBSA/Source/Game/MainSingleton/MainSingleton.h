#pragma once
class MainSingleton
{
public:
	static void Create();
	static void Destroy();

private:


	MainSingleton();
	~MainSingleton();
};

