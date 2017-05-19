// ============================================
// Name: Chris Banci
// Assignment: 3 - CPU Scheduling
// File type: Process header file
// ============================================
#pragma once

// enum for Process status
enum status_t { NEW, RUNNING, READY, WAITING, TERMINATED };

// implementation of a cpu Process
class Process {
public:
	int procID;					// ID of Process
	int priority;				// priority of Process
	status_t procStatus;		// state of Process

	int startTime;				// the arrival time of Process.
	int finishTime;				// the finish time of Process.
	int waitTime;				// the wait time of Process.
	int turnAroundTime;			// the turn around time of Process.
	int serviceTime;			// the service time of porcess.

	int totalCPUduration;		// total cpu duration of Process.
	int remainCPUduration;		// remaining cpu duration
	int avgCPUburstLength;		// avg burst length used for next burst length
	int nextCPUburstLength;		// predicted next cpu burst

	int totalIOburstTime;		// total time spent in io
	int IOburstTime;			// burst time for io

	int enterTime;				// the time the Process entered the ready queue.
	int triggerTime;			// the time the Process was dispatched from ready queue.

	void info();				// displays Process info

	Process();					// default constructor
	Process(int x);				// constructor to create Process with x ID.
};