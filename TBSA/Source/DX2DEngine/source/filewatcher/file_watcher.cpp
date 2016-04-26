#include "stdafx.h"
#include "filewatcher/file_watcher.h"
#include <fstream>

using namespace DX2D;

CFileWatcher::CFileWatcher()
	: myThread(nullptr)
	, myShouldEndThread(false)
	, myThreadIsDone(false)

{
}


CFileWatcher::~CFileWatcher()
{
	myShouldEndThread = true;
	if (myThread)
	{
		while (!myThreadIsDone)
		{
			Sleep(1);
		}
	}

}


void CFileWatcher::FlushChanges()
{
	if (!CEngine::GetInstance()->IsDebugFeatureOn(eDebugFeature_Filewatcher) || !myThread)
	{
		return;
	}
	std::lock_guard<std::mutex> guard(myMutex);


	myFileChanged.swap(myFileChangedThreaded);

	for (std::wstring& theString : myFileChanged)
	{
		std::wstring directoryOfFile(theString);
		directoryOfFile = directoryOfFile.substr(0, directoryOfFile.find_last_of(L"\\/"));

		std::wstring theFile(theString);
		theFile = theFile.substr(theFile.find_first_of(L"\\/") + 1, theFile.size());

		std::vector<callback_function_file> callbacks = myCallbacks[theFile];
		for (unsigned int i = 0; i < callbacks.size(); i++)
		{
			if (callbacks[i])
			{
				callbacks[i](theString);
			}
		}
	}


	myFileChanged.clear();


}

void CFileWatcher::UpdateChanges(const std::wstring& aDir)
{
	while (!myShouldEndThread)
	{
		myMutex.lock();
		OnFolderChange(aDir);
		myMutex.unlock();
	
		Sleep(10); // No need to hog too much performance
	}
	myThreadIsDone = true;
}

void CFileWatcher::OnFolderChange(const std::wstring& aDir)
{
	std::vector<WIN32_FIND_DATA> currentFolderFiles = GetAllFilesInFolder(aDir);
	std::vector<WIN32_FIND_DATA>& savedFolderFiles = myFolders[aDir];

	for (WIN32_FIND_DATA& currentFile : currentFolderFiles)
	{
		for (WIN32_FIND_DATA& savedFile : savedFolderFiles)
		{
			if (std::wstring(currentFile.cFileName).compare(savedFile.cFileName) == 0)
			{
				ULARGE_INTEGER currentFileTime;
				SYSTEMTIME currentFileTimeSystem;
				FileTimeToSystemTime(&currentFile.ftLastWriteTime, &currentFileTimeSystem);
				currentFileTime.LowPart = currentFile.ftLastWriteTime.dwLowDateTime;
				currentFileTime.HighPart = currentFile.ftLastWriteTime.dwHighDateTime;
				__int64 currentFileTime64 = currentFileTime.QuadPart;

				ULARGE_INTEGER savedFileTime;
				SYSTEMTIME savedFileTimeSystem;
				FileTimeToSystemTime(&savedFile.ftLastWriteTime, &savedFileTimeSystem);
				savedFileTime.LowPart = savedFile.ftLastWriteTime.dwLowDateTime;
				savedFileTime.HighPart = savedFile.ftLastWriteTime.dwHighDateTime;
				__int64 savedFileTime64 = savedFileTime.QuadPart;

				if (currentFileTime64 != savedFileTime64)
				{
					std::wstring fileThatChangedPath = aDir + L"\\" + std::wstring(currentFile.cFileName);
					bool isDependency = myDependencies.find(fileThatChangedPath) != myDependencies.end();
					if (isDependency)
					{
						std::vector<std::wstring>& deps = myDependencies[fileThatChangedPath];
						for (std::wstring& file : deps)
						{
							OnFileChange(file);
						}
						
					}
					else
					{
						OnFileChange(fileThatChangedPath);
					}

					// We have a change
					
					savedFile = currentFile;
				}
			}
		}
	}
}

void CFileWatcher::OnFileChange(std::wstring& aFile)
{
	for (unsigned int i = 0; i < myFileChangedThreaded.size(); i++)
	{
		if (myFileChangedThreaded[i].compare(aFile) == 0)
		{
			return;
		}
	}
	myFileChangedThreaded.push_back(aFile);

}

bool CFileWatcher::WatchFileChangeWithDependencies(std::wstring aFile, callback_function_file aFunctionToCallOnChange)
{
	if (!CEngine::GetInstance()->IsDebugFeatureOn(eDebugFeature_Filewatcher))
	{
		return false;
	}
	std::ifstream stream(aFile);
	if (!stream.good())
	{
		stream.close();
		return false;
	}

	std::wstring directoryOfFile(aFile);
	directoryOfFile = directoryOfFile.substr(0, directoryOfFile.find_last_of(L"\\/"));

	std::string line;
	const std::string includeString = "include";
	while (getline(stream, line))
	{
		std::size_t found = line.find(includeString);
		if (found != std::string::npos)
		{
			std::string foundFile(line);
			foundFile = foundFile.substr(foundFile.find_first_of("\"")+1, foundFile.size());
			foundFile = foundFile.substr(0, foundFile.find_last_of("\""));
			if (!foundFile.empty())
			{
				std::wstring depFile = directoryOfFile + L"\\" + ConvertStringToWstring(foundFile);
				WatchFileChange(depFile, aFunctionToCallOnChange);
				myDependencies[depFile].push_back(aFile);
			}
		}
	}
	
	stream.close();
	return WatchFileChange(aFile, aFunctionToCallOnChange);
}

bool CFileWatcher::WatchFileChange(std::wstring aFile, callback_function_file aFunctionToCallOnChange)
{
	if (!CEngine::GetInstance()->IsDebugFeatureOn(eDebugFeature_Filewatcher))
	{
		return false;
	}
	std::ifstream stream(aFile);
	if (!stream.good())
	{
		stream.close();
		return false;
	}
	stream.close();

	std::wstring directoryOfFile(aFile);
	directoryOfFile = directoryOfFile.substr(0, directoryOfFile.find_last_of(L"\\/"));

	std::wstring theFile(aFile);
	theFile = theFile.substr(theFile.find_first_of(L"\\/")+1, theFile.size());

	myCallbacks[theFile].push_back(aFunctionToCallOnChange);
	return WatchDirectory(directoryOfFile);
}

bool CFileWatcher::WatchDirectory(const std::wstring& aDir)
{
	FolderMap::iterator iter = myFolders.find(aDir);
	if (iter != myFolders.end())
	{
		//Already in our watch list
		return true;
	}

	myFolders[aDir] = GetAllFilesInFolder(aDir);

	myThread = new std::thread(&CFileWatcher::UpdateChanges, this, aDir);
	return true;
}

std::vector<WIN32_FIND_DATA> CFileWatcher::GetAllFilesInFolder(std::wstring aDir)
{
	std::vector<WIN32_FIND_DATA> filesInFolder;
	aDir += L"/*.*";
	WIN32_FIND_DATA fd;

	HANDLE hFind = ::FindFirstFile(aDir.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				filesInFolder.push_back(fd);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return filesInFolder;
}
