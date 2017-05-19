// ============================================================================
// Name: Chris Banci
// Date: 5/5/17
// Course: CS433 - Operating Systems
// Assignment: 5 - Simulation of Page Replacement Algorithms 
// File type: simulation.cpp - simulation implementation file
// ===========================================================================
#include <iostream>
#include "simulation.h"

using namespace std;

// PURPOSE: defualt constructor
simulation::simulation()
{
	pagesize = 0;	// the size of a page
	memorysize = 0;	// the total memory size
	selection = 0;	// the algorithm selected
	currentline = 0; // counter used for fifo
	linecounter = 0; // counter used in lru
	totalpagefaults = 0; // number of pages not found in page table
	totalreferences = 0; // number of references processed
	totalflushes = 0; // number of victim pages marked as dirty
	elapsed = 0.00;	// total time of simulation
}

// PURPOSE: This function displays the report for the simulation.
void simulation::report() {
	cout << "======= REPORT ======= " << endl;
	cout << "total memory references: " << totalreferences << endl;
	cout << "total page faults: " << totalpagefaults << endl;
	cout << "total flushes: " << totalflushes << endl;

	cout << "elapsed time: " << elapsed << " ms" << endl;
	cout << "====================== " << endl;
}

// PURPOSE: This function searches for a page in main memory.
// PARAMETERS: value = value to search in table;
// RETURN: index if value found, else -1;
int simulation::search(int value)
{
	for (int i = 0; i < page_table.size(); i++) {
		if (page_table[i].address == value) {
			return i;
		}
		else {
			return -1;
		}
	}
}

// PURPOSE: This function initializes a page_table with empty pages.
// PARAMETERS: size = how big to make the table.
void simulation::setup(int size)
{
	for (int i = 0; i < size; i++) {
		pageEntry p;
		p.address = 0;
		p.last = 0;
		p.dirty = false;
		p.valid = false;

		page_table.push_back(p);
	}
}

// PURPOSE: This is the FIFO paging replacement algorithm.
// PARAMTERS: &p = pagentry object
void simulation::FIFO(pageEntry &p)
{
	int victim = linecounter;

	linecounter++;
	linecounter = linecounter % page_table.size();

	page_table[victim] = p; // replacement

							// if victim page is dirty, increment total flushes count
	if (page_table[victim].dirty == true)
		totalflushes++;
}

// PURPOSE: This is the Random paging replacement algorithm.
// PARAMTERS: &p = pagentry object
void simulation::Random(pageEntry &p)
{
	int rand_num = rand() % page_table.size();
	int victim = rand_num;
	page_table[victim] = p;  // replacement

	// if victim page is dirty, increment total flushes count
	if (page_table[victim].dirty == true)
		totalflushes++;
}

// PURPOSE: This is the LRU paging replacement algorithm.
// PARAMTERS: &p = pagentry object
void simulation::LRU(pageEntry &p)
{
	int victim;

	// page is being used.
	if (page_table[linecounter].valid == false) {
		victim = linecounter;
		linecounter++;
		linecounter = linecounter % page_table.size();
	}

	// its being used, so find an unused page.
	else {
		int index = linecounter;
		int min = currentline;

		for (int i = 0; i < page_table.size(); i++) {
			if (page_table[i].last < min) {
				index = i;
				min = page_table[i].last;
			}
		}
		victim = index;

	}

	page_table[victim] = p; // replacement

	// if victim page is dirty, increment total flushes count
	if (page_table[victim].dirty == true)
		totalflushes++;
}