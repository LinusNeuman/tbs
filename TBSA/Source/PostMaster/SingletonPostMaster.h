#pragma once
#include <CU/DLDebug/DL_Debug.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/NameSpaceAliases.h>
#include "RecieverTypes.h"

class MessageReciever;
struct Message;

class SingletonPostMaster
{
public:
	static void Create();
	static void Destroy();

	static void AddReciever(const RecieverTypes aTypeToRecieve, MessageReciever & aRecieverToAdd);
	static void RemoveReciever(const RecieverTypes aTypeUnsubscribe, MessageReciever & aRecieverToRemove);

	static void RemoveReciever(MessageReciever &aReceiver);
	
	static bool CheckIfExists();
	

	static inline void PostMessage(const Message & aMessageToSend);
private:
	SingletonPostMaster();
	~SingletonPostMaster();

	void InternalPostMessage(const Message & aMessageToSend);

	static SingletonPostMaster * ourInstance;

	static inline SingletonPostMaster & GetInstance();

	CU::GrowingArray<CU::GrowingArray<MessageReciever*>> myRecievers;
};

inline SingletonPostMaster & SingletonPostMaster::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "PostMaster pointer is being used but it is nullptr");
	return *ourInstance;
}

inline void SingletonPostMaster::PostMessage(const Message & aMessageToSend)
{
	GetInstance().InternalPostMessage(aMessageToSend);
}