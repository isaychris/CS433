//=========================================================
// Assignment: 1 - Priority Queue of Processes
// Name: Chris Banci
// Compiler: g++
// File type: ReadyQueue implementation file
//===========================================================
#include "ReadyQueue.h"

// PURPOSE: Default constructor for MinHeap
ReadyQueue::ReadyQueue()
{
	// for optimization
	heap.data.reserve(20);
}

// PURPOSE:   Adds the PCB of a process into the ready queue.
// PARAMETER: &process = a reference to a process from the PCB_Table.
void ReadyQueue::insertProc(PCB& process)
{
	process.state = pcbStates::states_t::READY;
	heap.insert(process);
}

// PURPOSE: Remove and return the PCB with the highest priority from the queue
// RETURN:  temp = the process with the highest priorit being removed.
PCB* ReadyQueue::removeHighestProc() 
{
	auto* temp = heap.getMin();
	heap.deleteMin();
	temp->state = pcbStates::states_t::RUNNING;

	return temp;
}

// PURPOSE: Display the IDs, priorities and addresses of processes in the queue.
void ReadyQueue::displayQueue()
{
	heap.display();
}

// PURPOSE: Return the number of elements in the queue
int ReadyQueue::size()
{
	return heap.getSize();
}