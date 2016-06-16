#include "stdafx.h"
#include "ObserverPatternSubject.h"
#include "ObserverPatternListener.h"


ObserverPatternSubject::ObserverPatternSubject()
{
	myListeners.Init(3);
}


ObserverPatternSubject::~ObserverPatternSubject()
{
}

void ObserverPatternSubject::AddListener(ObserverPatternListener & aListenerToAdd)
{
	myListeners.Add(&aListenerToAdd);
}

void ObserverPatternSubject::RemoveListener(ObserverPatternListener & aListenerToRemove)
{
	myListeners.RemoveCyclic(&aListenerToRemove);
}


void ObserverPatternSubject::Broadcast(const Event & aEventToSend) const
{
	for (unsigned short iListener = 0; iListener < myListeners.Size(); ++iListener)
	{
 		myListeners[iListener]->RecieveEvent(aEventToSend);
	}
}