// ============================================
// Name: Chris Banci
// Assignment: 3 - CPU Scheduling
// File type: event header file
// ============================================
#pragma once

// enum for Event type
enum event_t { ARRIVAL, BURST_COMPLETE, IO_COMPLETE, TIME_EXPIRE };

// implementation of an Event
class Event {
public:
	int ID;				// the Process that belongs to Event.
	int time;			// time when Event should take place.
	event_t type;		// Event type.

	Event();			// default constructor
	Event(int pID, event_t etype, int etime);	// constructor to create Event
};