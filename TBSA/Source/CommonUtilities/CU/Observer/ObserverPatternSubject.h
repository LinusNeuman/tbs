#pragma once
#include "CU/GrowingArray/GrowingArray.h"

class ObserverPatternListener;
class Event;

class ObserverPatternSubject
{
public:
	void AddListener(ObserverPatternListener & aListenerToAdd);
	void RemoveListener(ObserverPatternListener & aListenerToRemove);

	void Broadcast(const Event & aEventToSend) const;

protected:
	CommonUtilities::GrowingArray<ObserverPatternListener*> myListeners;

	ObserverPatternSubject();
	virtual ~ObserverPatternSubject();
};