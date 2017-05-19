//=========================================================
// Assignment: 1 - Priority Queue of Processes
// Name: Chris Banci
// Compiler: g++
// File type: ReadyQueue header file
//===========================================================
#pragma once
#include "MinHeap.h"

// Priority Queue using the implementation of a MinHeap
class ReadyQueue {
public:
	MinHeap heap;							// ReadyQueue uses an implementation of a heap.

	PCB* removeHighestProc();				// Remove and return the PCB with the highest priority from the queue.
	void insertProc(PCB& process);			// Adds the PCB of a process into the ready queue.
	void displayQueue();					// Display the IDs and priorities of processes in the queue.
	int size();								// Return the number of elements in the queue.
	ReadyQueue();							// Default constructor for MinHeap.
};
