#include "stdafx.h"
#include "SingletonPostMaster.h"



SingletonPostMaster * SingletonPostMaster::ourInstance = nullptr;


void SingletonPostMaster::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new SingletonPostMaster();
	}
}

void SingletonPostMaster::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void SingletonPostMaster::AddReciever(const RecieverTypes aTypeToRecieve, MessageReciever & aRecieverToAdd, const RecieverOrder aPriority /*= RecieverOrder::eDefault*/)
{
	Reciever tempReciver(aRecieverToAdd, aRecieverToAdd.myRecieverOrder);
	if (aRecieverToAdd.myRecieverOrder != RecieverOrder::eDefault)
	{
		tempReciver = Reciever(aRecieverToAdd, aRecieverToAdd.myRecieverOrder);
	}
	
	if (GetInstance().myRecievers[USHORTCAST(aTypeToRecieve)].Find(tempReciver) != GetInstance().myRecievers.FoundNone)
	{
		return;
	}

	for (unsigned short iReciever = 0; iReciever < GetInstance().myRecievers[USHORTCAST(aTypeToRecieve)].Size(); ++iReciever)
	{
		if (tempReciver.myOrder < GetInstance().myRecievers[USHORTCAST(aTypeToRecieve)][iReciever].myOrder)
		{
			GetInstance().myRecievers[USHORTCAST(aTypeToRecieve)].Insert(iReciever, tempReciver);
			return;
		}
	}

	GetInstance().myRecievers[USHORTCAST(aTypeToRecieve)].Add(tempReciver);
}

void SingletonPostMaster::RemoveReciever(const RecieverTypes aTypeUnsubscribe, MessageReciever & aRecieverToRemove)
{
	Reciever tempReciever(aRecieverToRemove);
	GetInstance().myRecievers[USHORTCAST(aTypeUnsubscribe)].RemoveCyclic(tempReciever);
}

void SingletonPostMaster::RemoveReciever(MessageReciever& aReceiver)
{
	if (ourInstance == nullptr)
	{
		return;
	}

	for (int i = 0; i < static_cast<int>(RecieverTypes::enumlength); ++i)
	{
		RemoveReciever(static_cast<RecieverTypes>(i), aReceiver);
	}
}

bool SingletonPostMaster::CheckIfExists()
{
	return (ourInstance != nullptr);
}


SingletonPostMaster::SingletonPostMaster()
{
	myRecievers.Init(static_cast<unsigned short>(RecieverTypes::enumlength));
	for (unsigned short iRecieverTypes = 0; iRecieverTypes < static_cast<unsigned short>(RecieverTypes::enumlength); ++iRecieverTypes)
	{
		myRecievers.Add(CU::GrowingArray<Reciever>());
		myRecievers.GetLast().Init(5);
	}
}

SingletonPostMaster::~SingletonPostMaster()
{
}