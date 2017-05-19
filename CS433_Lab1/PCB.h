//=========================================================
// Assignment: 1 - Priority Queue of Processes
// Name: Chris Banci
// Compiler: g++
// File type: PCB header file
//===========================================================
#pragma once
#include <string>

// needed to resolve linker issues
namespace pcbStates {

	// pcbStates for process state
	enum states_t { NEW, WAITING, TERMINATED, RUNNING, READY };

	// Helper variable to display pcb enum states as a string 
	const std::string enumList[5] = { "NEW", "WAITING", "TERMINATED", "RUNNING", "READY" };
}

// Process control block (PCB) is a data structure representing a process in the system.
class PCB {
public:
	int ID;										// ID of process.
	int priority;								// Priority of process.
	pcbStates::states_t state;					// States of process.

	PCB();										// Default constructor.
	PCB(int i, pcbStates::states_t s, int p);	// Constructor of PCB.
};