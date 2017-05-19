// ============================================
// Name: Chris Banci
// Assignment: 3 - CPU Scheduling
// File type: Simulation header file
// ============================================
#pragma once
#include <queue>
#include "event.h"
#include "process.h"

// enum for CPU state
enum state_t { BUSY, IDLE };

// overrides priority queues comparison logic. comparison based on Event time
struct EventCompare {
	bool operator() (const Event* e1, const Event* e2) const {
		return e1->time > e2->time; 
	}
};

// implementation of CPU
struct CPU {
	Process * CPU_JOB;				// holds current Process
	state_t CPU_STATE;				// current state of cpu
};

// implementation of DES Simulation
class Simulation {
public:
	std::priority_queue<Event*, std::vector<Event*>, EventCompare> event_queue;		// Event queue for DES
	std::vector<Process> process_table;		// all processes in system
	
	CPU _CPU;						// central processing unit.
	int currentTime;				// Simulation current time.
	int quitTime;					// Simulation duration time.
	int selection;					// scheduler type selection.
	int amount;						// number of processes to simulate.
	int completedJobs;				// total completed jobs in Simulation.

	void runFCFS();					// runs fcfs scheduler
	void runSJF();					// runs sjb scheduler
	void report();					// displays report of Simulation
	void setup();					// creates x amount of processes
	void displayTable();			// displays all processes in the system
	Simulation();					// default constructor

private:
	double utilizeCPU;				// utlizatation of cpu
	double throughput;				// throughput of completed jobs / s
	double avgTurnAround;			// average turnaround time of processes.
	double avgWaitTime;				// average wait time of processes
};