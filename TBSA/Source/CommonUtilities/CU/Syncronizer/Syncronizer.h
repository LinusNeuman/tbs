#pragma once

#include <thread>

#include "CU/GrowingArray/GrowingArray.h"

namespace CommonUtilities
{

	namespace Thread
	{

		template<typename TYPE>
		class Syncronizer
		{
		public:

			typedef void (TYPE::*functionPointer)(void);

			Syncronizer();
			~Syncronizer();

			void Start();
			void Run();
			void Stop();

			void AddThreadMethod(functionPointer aFunctionPointer, TYPE &aMember);

		private:

			class ThreadData
			{
			public:

				inline ThreadData();
				inline ThreadData(functionPointer aFunctionPointer, TYPE &aMember);
				inline ~ThreadData();
				
				inline ThreadData& operator=(const ThreadData &aSource);

				inline volatile bool IsDone();
				inline void Start();
				inline void Reset();
				inline void Stop();

				inline void Join();

			private:

				std::thread myThread;
				functionPointer myFunctionPointer;
				TYPE *myMember;

				volatile bool myIsRunning;
				volatile bool myIsDone;

				inline void Run();

			};

			CommonUtilities::GrowingArray<ThreadData> myThreads;

		};

	}

}

#include "Syncronizer.inl"
