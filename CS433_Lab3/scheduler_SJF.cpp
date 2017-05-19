// ============================================
// Name: Chris Banci
// Assignment: 3 - CPU Scheduling
// File type: SJF scheduler implementation file
// ============================================
#include <iostream>
#include "random.h"
#include "scheduler_SJF.h"
#include "simulation.h"
using namespace std;

// PURPOSE: default constructor
SJF::SJF()
{
	DES = nullptr;
}

// PURPOSE: constructor to create SJF object.
// PARAMETER: s = used to access Simulation member variables.
SJF::SJF(Simulation * s)
{
	DES = s;
}

// PURPOSE: This function dispatches a Process.
void SJF::schedule()
{
	// dispatch Process
	if (DES->_CPU.CPU_STATE == IDLE && !ready_queue.empty()) {
		// select Process to schedule from ready queue.
		Process * p = ready_queue.top();
		ready_queue.pop();

		//  - 1) assign Process to cpu.
		DES->_CPU.CPU_JOB = p;
		DES->_CPU.CPU_STATE = BUSY;
		p->procStatus = RUNNING;
		p->triggerTime = DES->currentTime;

		// - 2) create Event for the time when Process' cpu burst will complete.
		int time = DES->currentTime + p->nextCPUburstLength;
		Event * cpucompletion = new Event(p->procID, BURST_COMPLETE, time);

		// - 3) add Event to Event queue.
		DES->event_queue.push(cpucompletion);
	}
}

// PURPOSE: This function handles an Event from event_queue.
// PARAMETER: &e = Event from event_queue.
void SJF::handle_event(Event & e)
{
	switch (e.type) {
	case ARRIVAL:
		handle_process_arrival(e);
		break;

	case BURST_COMPLETE:
		handle_cpuburst_completion(e);
		break;

	case IO_COMPLETE:
		handle_io_completion(e);
		break;

	case TIME_EXPIRE:
		handle_timer_expiration(e);
		break;
	}
}

// PURPOSE: This function handles a Process arrival Event.
// PARAMETER: &e = Process arrival Event
void SJF::handle_process_arrival(Event & e)
{
	Process * p = &DES->process_table[e.ID];

	// generate processes next cpu burst length
	p->nextCPUburstLength = CPUBurstRandom(p->avgCPUburstLength);

	// add Process to ready queue.
	p->enterTime = DES->currentTime;
	p->procStatus = READY;
	ready_queue.push(p);

	schedule();
}

// PURPOSE: This function handles a cpu completion Event
// PARAMETER: &e = cpu completion Event
void SJF::handle_cpuburst_completion(Event & e)
{
	Process * p = &DES->process_table[e.ID];

	// update remaining cpu duration
	p->remainCPUduration -= p->nextCPUburstLength;

	// update stats info
	p->serviceTime += p->nextCPUburstLength;
	p->waitTime = p->waitTime + (p->triggerTime - p->enterTime);

	// when Process is complete
	if (p->remainCPUduration <= 0) {
		cout << "[clock: " << DES->currentTime / 1000 << "] - Process " << p->procID << " complete!" << endl;

		// update Process info
		DES->completedJobs++;
		p->turnAroundTime = DES->currentTime - p->startTime;
		p->finishTime = DES->currentTime;

		// remove Process from cpu.
		p->procStatus = TERMINATED;
		DES->_CPU.CPU_JOB = nullptr;
	}

	else {
		// generate next io burst length.
		p->IOburstTime = ranInt(30, 100);

		// create Event for time when Process completes io burst.
		int time = DES->currentTime + p->IOburstTime;
		Event * iocompletion = new Event(e.ID, IO_COMPLETE, time);
		DES->event_queue.push(iocompletion);
	}

	DES->_CPU.CPU_STATE = IDLE;
	schedule();
}

// PURPOSE: This function handles a io completion Event
// PARAMETER: &e = io completion Event
void SJF::handle_io_completion(Event & e)
{
	Process * p = &DES->process_table[e.ID];

	// generate the processes next cpu burst length
	p->nextCPUburstLength = CPUBurstRandom(p->avgCPUburstLength);
	p->totalIOburstTime += +p->IOburstTime;

	// move the Process to ready queue.
	p->procStatus = READY;
	p->enterTime = DES->currentTime;
	ready_queue.push(p);

	schedule();
}

// PURPOSE: This function handles a timer expiration Event used in preemptive schedulers.
// PARAMETER: &e = time expiration Event.
void SJF::handle_timer_expiration(Event & e)
{
	Process * p = &DES->process_table[e.ID];
	p->procStatus = READY;
	ready_queue.push(p);

	p->nextCPUburstLength = CPUBurstRandom(p->avgCPUburstLength);

	DES->_CPU.CPU_STATE = IDLE;
	schedule();
}
