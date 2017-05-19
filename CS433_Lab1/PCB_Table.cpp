//=========================================================
// Assignment: 1 - Priority Queue of Processes
// Name: Chris Banci
// Compiler: g++
// File type: PCB_Table implementation file
//===========================================================
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include "PCB_Table.h"

// PURPOSE: Default constructor for pcb process_list.
PCB_Table::PCB_Table()
{
	// for optimization
	process_list.reserve(20);
	helper.reserve(50);

	// initializes helper list with 20 numbers.
	// used to keep track of what processes are not in the readyqueue.
	for (auto i = 1; i <= 20; i++) {
		helper.emplace_back(i);
	}

	// shuffles the list
	std::random_shuffle(helper.begin(), helper.end());

	// seeding the random generator
	std::random_device rd;
	mt_rand.seed(rd());
}


// PURPOSE:	  Creates pcb process_list with x pcb elements
// PARAMETER: x = size of process_list
void PCB_Table::makeTable(int n)
{
	for (auto i = 1; i <= n; i++) {
		PCB newPCB(i, pcbStates::states_t::NEW, i);
		process_list.emplace_back(newPCB);
	}
}

// PURPOSE:   Returns a pcb from the process_list
// PARAMETER: index = index of PCB_Table.
// RETURN:    process_list[index - 1] = return the reference of the pcb at process_list[index - 1]
PCB& PCB_Table::getProcess(int index)
{
	return process_list[index - 1];
}

// PURPOSE: Displays the contents of pcb process_list
void PCB_Table::display()
{
	std::cout << std::left << std::setw(5) << "ID " << std::setw(11) << "Priority " << std::setw(13) << "State " << std::setw(15) << "Address" << "Size = " << process_list.size() << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;

	for (auto i = 0; i < process_list.size(); ++i) {
		std::cout << std::left << std::setw(8) << process_list[i].ID << std::setw(8) << process_list[i].priority << std::setw(13) << pcbStates::enumList[process_list[i].state] << std::setw(10) << &process_list[i] << std::endl;
	}
}
