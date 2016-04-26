#pragma once

class Event;

class ObserverPatternListener
{
public:
	virtual void RecieveEvent(const Event & aEventToTrigger) = 0;

protected:
	ObserverPatternListener();
	virtual ~ObserverPatternListener();

	
};