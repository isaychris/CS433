//=========================================================
// Assignment: 1 - Priority Queue of Processes
// Name: Chris Banci
// Compiler: g++
// File type: Driver file
//===========================================================
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include "PCB.h"
#include "PCB_Table.h"
#include "ReadyQueue.h"


// PURPOSE: Test 1 of the lab. Tests the implmentation of funcions insertProc(), removeHighestProc() and displayQueue().
void test1(ReadyQueue &q1, PCB_Table &p1)
{
	std::cout << "// TEST 1\n";

	// START OF TEST 1 =======================================================================
	p1.makeTable(20);

	// (a) add processes 5, 1, 8, 11 to q1. Display the content of q1
	q1.insertProc(p1.getProcess(5));
	q1.insertProc(p1.getProcess(1));
	q1.insertProc(p1.getProcess(8));
	q1.insertProc(p1.getProcess(11));
	q1.displayQueue();

	// (b) remove the process with the highest priority from q1 and display q1
	q1.removeHighestProc();
	q1.displayQueue();

	// (c) remove the process with the highest priority from q1 and display q1
	q1.removeHighestProc();
	q1.displayQueue();

	// (d) insertSort processes 3, 7, 2, 12, 9 to q1
	q1.insertProc(p1.getProcess(3));
	q1.insertProc(p1.getProcess(7));
	q1.insertProc(p1.getProcess(2));
	q1.insertProc(p1.getProcess(12));
	q1.insertProc(p1.getProcess(9));

	// (e) One by one remove the process with the highest priority from the queue q1 and display it after each removal.
	while (!q1.heap.data.empty()) {
		q1.removeHighestProc();
		q1.displayQueue();
	}
	// END OF TEST 1 ==========================================================================
}

// PURPOSE: Test 2 of the lab
void test2(ReadyQueue &q1, PCB_Table &p1)
{
	std::cout << "// TEST 2\n";

	std::vector<int> random;		// random priorities between 1-50
	std::vector<int> selection;		// random 0 & 1's for selection.

	std::random_device rd;			// to seed mt_rand
	std::mt19937 mt_rand(rd());		// random generator


	// to reduce significant overhead during the timing of test2,
	// random priorities are generated before hand and are assigned to processes
	// when they are added to readyqueue through index iteration.
	for (int i = 0; i < 1000000; ++i) {
		selection.emplace_back(mt_rand() % 2);
	}

	// also for selection aswell.
	for (int i = 0; i < 1000010; ++i) {
		random.emplace_back(mt_rand() % 50 + 1);
	}

	// randomly inserting 10 processes from pcb_table
	for (int i = 0; i < 10; ++i) {
		auto& temp = p1.getProcess(p1.helper.back());
		temp.priority = random[1000000 + i];
		q1.insertProc(temp);
		p1.helper.pop_back();
	}

	auto begin = std::chrono::high_resolution_clock::now();

	// START OF TEST 2 ========================================================================
	for (auto j = 0; j < 1000000; ++j) {
		// (a) Randomly decide to remove a process from or add a process to the ready queue with equal probability (50 % chance).

		switch (selection[j]) {

			// remove process with the highest priority from readyqueue.
			// if readyqueue is empty, dont remove from readyqueue.
			case 0:
				if (!q1.heap.data.empty()) {
					p1.helper.emplace_back(q1.removeHighestProc()->ID);
				}
				break;


			// add process from pcb_table to readyqueue with random priority.
			// if all processes from pcb table are in q1, dont add anymore processes.
			case 1:
				if (!p1.helper.empty()) {
					auto& temp = p1.getProcess(p1.helper.back());
					temp.priority = random[j];
					q1.heap.insert(temp);
					p1.helper.pop_back();
				}
				break;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	double elapsedTime = std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count();
	// END OF TEST 2 ==========================================================================

	q1.displayQueue();
	std::cout << "Test 2 elapsed time: " << elapsedTime / 1000 << " ms.\n";
}


// PURPOSE: The driver to test out the implementation of a priority queue.
int main()
{
	std::cout << "// Author: Chris Banci\n";
	std::cout << "// Assignment: 1\n";
	std::cout << "// Date: 2/07/17\n\n";

	ReadyQueue q1;		
	PCB_Table p1;

	test1(q1, p1);
	test2(q1, p1);

	//std::cout << "// PCB_TABLE " << std::endl;
	//p1.display();
}

