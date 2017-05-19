//=========================================================
// Assignment: 1 - Priority Queue of Processes
// Name: Chris Banci
// Compiler: g++
// File type: MinHeap header file
//===========================================================
#pragma once
#include <vector>
#include "PCB.h"

// Heap data structure to implement ReadyQueue
class MinHeap {
public:
	std::vector<PCB*> data;					// Vector that will hold the heap elements.

	void insert(PCB & value);				// Inserts new value into heap.
	void deleteMin();						// Deletes the min value at root.
	void display();							// Displays the heap as an array list.
	PCB* getMin();							// Returns smallest value from the root.
	int getSize();							// Retuns the size of the heap.
	MinHeap();								// Default constructor.

private:
	void bubbleDown(int index);				// Bubbles down the node at index to correct position in the tree using recursion.
	void bubbleUp(int index);				// Bubbles up the node at index to correct position in the tree using recursion.
	int size;								// The size of the heap.
};