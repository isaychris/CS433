// ============================================
// Name: Chris Banci
// Assignment: 3 - CPU Scheduling
// File type: Event implementation file
// ============================================
#include "event.h"

// PURPOSE: default constructor for Event
Event::Event()
{
	ID = 0;
	type = ARRIVAL;
	time = 0;
}

// PURPOSE: constructor to create an Event 
// PARAMETER: pID = Process to which the Event belongs to
//			  etype = type of Event
//			  etime = time of Event
Event::Event(int pID, event_t etype, int etime)
{
	ID = pID;
	type = etype;
	time = etime;
}

