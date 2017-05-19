//=========================================================
// Assignment: 1 - Priority Queue of Processes
// Name: Chris Banci
// Compiler: g++
// File type: PCB implementation file
//===========================================================
#include "PCB.h"

// PURPOSE: Default constructor for a process
PCB::PCB() 
{
	ID = 0;
	state = pcbStates::states_t::NEW;
	priority = 0;
}

// PURPOSE: Constructor for pcb
// PARAMETER: i = ID of pcb
//			  s = state of pcb
//			  p = priority of pcb
PCB::PCB(int i, pcbStates::states_t s, int p) 
{
	ID = i;
	state = s;
	priority = p;
}