#include "stdafx.h"
//#include "MainSingleton.h"
//#include "Rend/RenderConverter.h"
//
//MainSingleton * MainSingleton::ourInstance = nullptr;
//
//void MainSingleton::Create()
//{
//	if (ourInstance == nullptr)
//	{
//		DL_PRINT("MainSingleton Created");
//		ourInstance = new MainSingleton();
//	}
//	else
//	{
//		DL_PRINT("Create was called on none nullptr MainSingleton");
//	}
//}
//
//void MainSingleton::Destroy()
//{
//	if (ourInstance != nullptr)
//	{
//		DL_PRINT("MainSingleton Created");
//		SAFE_DELETE(ourInstance);
//	}
//	else
//	{
//		DL_PRINT("Destroy was called on MainSingleton but it was already nullptr");
//	}
//}
//
//void MainSingleton::Init()
//{
//	GetInstance().CreateInstances();
//}
//
//
//
//void MainSingleton::CreateInstances()
//{
//	myRenderer = new RenderConverter();
//}



//MainSingleton::MainSingleton()
//{
//}
//
//
//MainSingleton::~MainSingleton()
//{
//}