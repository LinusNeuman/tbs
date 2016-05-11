#pragma once
//
//class RenderConverter;
//
//class MainSingleton
//{
//public:
//	static void Create();
//	static void Destroy();
//
//	static void Init();
//
//	static RenderConverter & GetRenderer();
//
//private:
//	void CreateInstances();
//
//	static MainSingleton & GetInstance();
//
//	static MainSingleton * ourInstance;
//
//	RenderConverter * myRenderer;
//
//	MainSingleton();
//	~MainSingleton();
//};
//
//inline MainSingleton & MainSingleton::GetInstance()
//{
//	DL_ASSERT(ourInstance != nullptr, "MainSingleton is nullptr");
//	return *ourInstance;
//}
//
//inline RenderConverter & MainSingleton::GetRenderer()
//{
//	DL_ASSERT(GetInstance().myRenderer != nullptr, "Renderer in MainSingleton is nullptr");
//	return *GetInstance().myRenderer;
//}