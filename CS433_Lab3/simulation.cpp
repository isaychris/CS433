// ============================================
// Name: Chris Banci
// Assignment: 3 - CPU Scheduling
// File type: simulation implementation file
// ============================================
#include <iomanip>
#include <iostream>
#include "process.h"
#include "scheduler_FCFS.h"
#include "scheduler_SJF.h"
#include "simulation.h"
using namespace std;

// PURPOSE: default constructor for Simulation
Simulation::Simulation()
{
	_CPU.CPU_JOB = nullptr;
	_CPU.CPU_STATE = IDLE;
	currentTime = 0;
	quitTime = 300000;			// DES Simulation duration is 5 minutes.
	selection = 0;
	amount = 0;

	utilizeCPU = 0;
	throughput = 0;
	avgTurnAround = 0;
	avgWaitTime = 0;
	completedJobs = 0;
}

// PURPOSE: Generates a report for the chosen scheduler. times represented in seconds.
void Simulation::report()
{
	int totalTurnAround = 0;
	int totalWaitTime = 0;
	int totalCPU = 0;
	int totalIO = 0;

	cout << "---------------------------------------------------------" << endl;
	cout << left << setw(5) << "ID" << setw(10) << "arrival" << setw(9) << "finish"
		<< setw(11) << "service" << setw(15) << "turnaround" << "wait" << endl;
	cout << "---------------------------------------------------------" << endl;

	for (int i = 0; i < process_table.size(); i++) {
		totalTurnAround += process_table[i].turnAroundTime;
		totalWaitTime += process_table[i].waitTime;
		totalCPU += process_table[i].serviceTime;
		totalIO += process_table[i].totalIOburstTime;

		cout << left << setw(7) << process_table[i].procID << setw(9) << process_table[i].startTime / 1000
			<< setw(10) << process_table[i].finishTime / 1000 << setw(13) << process_table[i].serviceTime / 1000
			<< setw(12) << process_table[i].turnAroundTime / 1000 << process_table[i].waitTime / 1000 << endl;
	}

	utilizeCPU = double(totalCPU) / quitTime;
	throughput = double(completedJobs) / quitTime;
	avgTurnAround = (completedJobs == 0) ? 0 : (totalTurnAround / completedJobs);
	avgWaitTime = (totalWaitTime / amount);
	cout << "**Process times shown in seconds**" << endl << endl;

	cout << "Jobs Completed: " << completedJobs << endl;
	cout << "CPU Utilization: " << fixed << setprecision(2) << (utilizeCPU * 100) << " %" << endl;
	cout << "Throughput: "  << fixed << setprecision(3) << (throughput * 1000) << " jobs / sec"  << endl;
	cout << "Avg Turnaround Time: " << fixed << setprecision(2) << avgTurnAround / 1000 << " sec" << endl;
	cout << "Avg Wait Time: " << fixed << setprecision(2) << avgWaitTime / 1000 << " sec" << endl;
	cout << "---------------------------------------------------------" << endl << endl;
}

// PURPOSE: initialize event_queue with randomly generated processes.
void Simulation::setup()
{
	cout << "Generating " << amount << " processes ..." << endl;
	// initialize process_table with x amount of processes.
	for (auto i = 0; i < amount; i++) {
		Process proc(i);
		process_table.push_back(proc);

		// push Process arrival events to Event queue
		Event * inital = new Event(i, ARRIVAL, proc.startTime);
		event_queue.push(inital);
	}
}

// PURPOSE: runs the FCFS scheduler
void Simulation::runFCFS()
{
	FCFS fcfs_scheduler(this);
	cout << "Running FCFS Scheduler ..." << endl;

	while (!event_queue.empty() && currentTime < quitTime) {
		// select Event from Event queue
		Event * e = event_queue.top();
		event_queue.pop();

		// forward currentTime.
		currentTime = e->time; 		

		// execute the Event
		fcfs_scheduler.handle_event(*e);
	}

	cout << "Stopping FCFS Scheduler ..." << endl;
	//displayTable();
}

// PURPOSE:: the runs SJF scheduler 
void Simulation::runSJF()
{
	SJF SJF_scheduler(this);
	cout << "Running SJF Scheduler ..." << endl;

	while (!event_queue.empty() && currentTime < quitTime) {
		// select Event from Event queue
		Event * e = event_queue.top();
		event_queue.pop();

		// forward currentTime.
		currentTime = e->time;

		// execute the Event
		SJF_scheduler.handle_event(*e);
	}

	cout << "Stopping SJF Scheduler ..." << endl << endl;
	//displayTable();
}

// PURPOSE: displays all the processes and its info in the system
void Simulation::displayTable()
{
	cout << left << setw(7) << "ID" << setw(7) << "pr" << setw(7) << "sts" << setw(7) << "start" 
		<< setw(7) << "remain" << setw(7) << "total" << setw(7) << "avg" << setw(7) << "nxt" 
		<< setw(7) << "io" << setw(7) << "fin" << setw(7) << "turn" << setw(7) << "wait" << endl;

	cout << "---------------------------------------------------------------------------------" << endl;
	for (auto i = 0; i < process_table.size(); i++) {
		process_table[i].info();
	}
	cout << "---------------------------------------------------------------------------------" << endl << endl;
}