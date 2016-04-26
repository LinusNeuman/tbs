#include "Syncronizer.h"

namespace CommonUtilities
{

	namespace Thread
	{

		template<typename TYPE>
		Syncronizer<TYPE>::Syncronizer()
		{

			myThreads.Init(2);

		}
		template<typename TYPE>
		Syncronizer<TYPE>::~Syncronizer()
		{

			Stop();

		}

		template<typename TYPE>
		inline void Syncronizer<TYPE>::Start()
		{
			myThreads.Optimize();
			for (unsigned short i = 0; i < myThreads.Size(); ++i)
			{
				myThreads[i].Start();
			}
		}
		template<typename TYPE>
		inline void Syncronizer<TYPE>::Run()
		{

			for (unsigned short i = 0; i < myThreads.Size(); ++i)
			{
				myThreads[i].Reset();
			}

			for (unsigned short i = 0; i < myThreads.Size(); ++i)
			{
				while (myThreads[i].IsDone() == false)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}

		}
		template<typename TYPE>
		inline void Syncronizer<TYPE>::Stop()
		{
			if (myThreads.Size() > 0)
			{
				for (unsigned short i = 0; i < myThreads.Size(); ++i)
				{
					myThreads[i].Stop();
				}
				for (unsigned short i = 0; i < myThreads.Size(); ++i)
				{
					myThreads[i].Join();
				}
				myThreads.RemoveAll();
			}
		}

		template<typename TYPE>
		void Syncronizer<TYPE>::AddThreadMethod(functionPointer aFunctionPointer, TYPE &aMember)
		{
			myThreads.Add(ThreadData(aFunctionPointer, aMember));
		}

		template<typename TYPE>
		inline Syncronizer<TYPE>::ThreadData::ThreadData()
		{
			myIsDone = false;
			myIsRunning = true;
		}
		template<typename TYPE>
		inline Syncronizer<TYPE>::ThreadData::ThreadData(functionPointer aFunctionPointer, TYPE &aMember)
		{
			myIsDone = true;
			myIsRunning = true;
			myFunctionPointer = aFunctionPointer;
			myMember = &aMember;
		}
		template<typename TYPE>
		inline Syncronizer<TYPE>::ThreadData::~ThreadData()
		{
			myIsDone = true;
			myIsRunning = false;
		}

		template<typename TYPE>
		inline typename Syncronizer<TYPE>::ThreadData& Syncronizer<TYPE>::ThreadData::operator=(const ThreadData &aSource)
		{
			myIsDone = aSource.myIsDone;
			myIsRunning = aSource.myIsRunning;
			myFunctionPointer = aSource.myFunctionPointer;
			myMember = aSource.myMember;
			return *this;
		}

		template<typename TYPE>
		inline volatile bool Syncronizer<TYPE>::ThreadData::IsDone()
		{
			return myIsDone;
		}
		template<typename TYPE>
		inline void Syncronizer<TYPE>::ThreadData::Start()
		{
			myThread = std::thread(&Syncronizer::ThreadData::Run, this);
		}
		template<typename TYPE>
		inline void Syncronizer<TYPE>::ThreadData::Reset()
		{
			myIsDone = false;
		}
		template<typename TYPE>
		inline void Syncronizer<TYPE>::ThreadData::Stop()
		{
			myIsRunning = false;
		}

		template<typename TYPE>
		inline void Syncronizer<TYPE>::ThreadData::Join()
		{
			myThread.join();
		}

		template<typename TYPE>
		inline void Syncronizer<TYPE>::ThreadData::Run()
		{
			while (myIsRunning == true)
			{
				if (myIsDone == false)
				{
					(myMember->*myFunctionPointer)();
					myIsDone = true;
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
		}

	}

}
