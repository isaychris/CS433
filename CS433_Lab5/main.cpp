// ============================================================================
// Name: Chris Banci
// Date: 5/7/17
// Course: CS433 - Operating Systems
// Assignment: 5 - Simulation of Page Replacement Algorithms 
// File type: main.cpp - driver file
// ===========================================================================
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>	
#include "simulation.h"

using namespace std;

void prompt(simulation &assign5)
{
	// selection for paging algorithm
	cout << "Select Paging algorithm:" << endl;
	cout << "0 - Random" << endl;
	cout << "1 - FIFO" << endl;
	cout << "2 - LRU" << endl << endl;
	cout << ">> ";
	cin >> assign5.selection;

	while (assign5.selection > 2 || assign5.selection < 0) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "[Error] enter again: ";
		cin >> assign5.selection;
	}

	switch (assign5.selection) {
	case 0: cout << "Running Random Paging algorithm ... " << endl; break;
	case 1: cout << "Running FIFO Paging algorithm ... " << endl; break;
	case 2: cout << "Running LRU Paging algorithm ... " << endl; break;
	}
}

void handleargs(int argc, simulation &assign5)
{
	// input handling for commandline
	if (argc < 3 || argc > 3) {
		std::cout << "Usage: ./assign5 <pagesize> <memorysize> " << std::endl;
		exit(1);
	}
	if (((assign5.pagesize & (assign5.pagesize - 1)) != 0 || ((assign5.memorysize & (assign5.memorysize - 1)) != 0))) {
		cout << "error, input needs to be power of 2" << endl;
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	cout << "// Name: Chris Banci" << endl;
	cout << "// Date : May 7, 2017" << endl;
	cout << "// Course : CS433 - Operating Systems" << endl;
	cout << "// Assignment : 5 - Simulation of Page Replacement Algorithms " << endl;
	cout << "---------------------------------------------------------" << endl << endl;

	simulation assign5;
	assign5.pagesize = atoi(argv[1]); // argument 1
	assign5.memorysize = atoi(argv[2]); // argument 2

	// argument error handling
	handleargs(argc, assign5);

	// prompt to ask for algorithm selection.
	prompt(assign5);

	// initialize page table;
	int size = assign5.memorysize / assign5.pagesize;
	assign5.setup(size);

	// start the simulation timer
	auto begin = std::chrono::high_resolution_clock::now(); 

	// read file until it ends
	ifstream file("references.txt");
	string line;

	while (file >> line) {
		int value = stoi(line);
		int lastdigit = value % 10;	// extract the last digit from value.
		bool bit;

		// check the last digit of the line
		if (lastdigit % 2 == 1)	//if last digit is odd, set dirty bit.
			bit = true;
		else 
			bit = false; // last digit is even.

		// search for value in page_table
		int index = assign5.search(value); 

		// if the location returned is not -1, then it exists in the page_table.
		if (index >= 0) {
			assign5.page_table[index].dirty = bit;
			assign5.page_table[index].last = assign5.currentline;
		}

		// the value was not found, so generate fault, and place page into page_table.
		else {
			pageEntry temp(value - bit, bit, true, assign5.currentline);
			assign5.totalpagefaults++;

			// use selected algorithm to place page into page_table.
			switch (assign5.selection) {
			case 0:
				assign5.Random(temp);
				break;
			case 1:
				assign5.FIFO(temp);
				break;
			case 2:
				assign5.LRU(temp);
				break;
			}
		}

		assign5.totalreferences++;	// how many lines have been parsed.
	}


	// end the timer
	auto end = std::chrono::high_resolution_clock::now();
	assign5.elapsed = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();

	//display the report
	assign5.report();

	return 0;
}
