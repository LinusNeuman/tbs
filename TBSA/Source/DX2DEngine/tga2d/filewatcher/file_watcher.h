#pragma once
#include <functional>
#include <windows.h>
#include <thread>
#include <mutex>

namespace DX2D
{
	typedef std::function<void(const std::wstring&)> callback_function_file;
	class CFileWatcher
	{
	public:
		CFileWatcher();
		~CFileWatcher();

		/* Will check the file for includes and add them as well*/
		bool WatchFileChangeWithDependencies(std::wstring aFile, callback_function_file aFunctionToCallOnChange);
		bool WatchFileChange(std::wstring aFile, callback_function_file aFunctionToCallOnChange);


		void FlushChanges();
	private:
		void UpdateChanges(const std::wstring& aDir);
		void OnFolderChange(const std::wstring& aDir);
		bool WatchDirectory(const std::wstring& aDir);
		void OnFileChange(std::wstring& aFile);
		std::vector<WIN32_FIND_DATA> GetAllFilesInFolder(std::wstring aDir);

		std::thread* myThread;

		typedef std::map<std::wstring, std::vector<WIN32_FIND_DATA>> FolderMap;
		FolderMap myFolders;

		std::vector<std::wstring> myFileChangedThreaded;
		std::vector<std::wstring> myFileChanged;
		std::map<std::wstring, std::vector<callback_function_file> > myCallbacks;

		typedef std::map<std::wstring, std::vector<std::wstring>> Dependencies;
		Dependencies myDependencies;

		std::mutex myMutex;
		bool myShouldEndThread;
		bool myThreadIsDone;
	};

}