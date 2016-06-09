#pragma once
class SingletonDataHolder
{
public:
	static void Create();
	static void Destroy();

	//static void Init;

private:
	static SingletonDataHolder * ourInstance;

	static SingletonDataHolder & GetInstance();

	SingletonDataHolder();
	~SingletonDataHolder();
};