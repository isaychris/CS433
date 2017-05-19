//=========================================================
// Assignment: 1 - Priority Queue of Processes
// Name: Chris Banci
// Compiler: g++
// File type: PCB_Table header file
//===========================================================
#pragma once
#include <random>
#include <vector>
#include "PCB.h"

// Data structure that contains all processes currently in the system. 
class PCB_Table {
public:
	std::vector<PCB> process_list;				// Vector that contains all processes in the system.
	std::vector<int> helper;					// Helper vector used to track which processes are not in readyQueue.

	void makeTable(int n);						// Makes a process_list with size n.
	void display();								// Displays the contents of pcb_table.
	PCB& getProcess(int index);					// Returns a process from pcb_table at index.
	PCB_Table();								// Default constructor for PCB_Table.
	
private:
	std::mt19937 mt_rand;						// Random generator engine
};
