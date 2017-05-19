//=========================================================
// Assignment: 1 - Priority Queue of Processes
// Name: Chris Banci
// Compiler: g++
// File type: MinHeap implementation file
//===========================================================
#include <iomanip>
#include <iostream>
#include <string>
#include "MinHeap.h"

// PURPOSE: Default constructor.
MinHeap::MinHeap() 
{
	size = 0;
}

// PURPOSE: Bubbles down the node to correct position in the tree using recursion.
// PARAMETER: index = node at [index] to bubble down.
void MinHeap::bubbleDown(int index) 
{
	auto length = data.size();						// size of vector
	auto leftChildIndex = 2 * index + 1;			// the left child index.
	auto rightChildIndex = 2 * index + 2;			// the right child index.

	// if the left child at index is greater than the size of vector, index is a leaf.
	if (leftChildIndex >= length) {
		return;
	}

	// the smaller node.
	auto minIndex = index;					

	// if node at [index] is greater than the node at [index] left child
	if (data[index]->priority > data[leftChildIndex]->priority) {
		minIndex = leftChildIndex;					// the smaller node is the left child.
	}

	// if the right child at [index] is less than vector size
	// and the node at [minindex] is greater than the right child node of [index]
	if ((rightChildIndex < length) && (data[minIndex]->priority > data[rightChildIndex]->priority)) {
		minIndex = rightChildIndex;					// the smaller node is the rightchild.
	}

	// if minIndex is not equal to index, then swap because minIndex is smaller.
	if (minIndex != index) {
		auto * temp = data[index];					// temp variable to hold value at index
		data[index] = data[minIndex];				// set index to minindex.
		data[minIndex] = temp;						// then restore minindex from temp.
		bubbleDown(minIndex);						// bubble down minindex recursively
	}
}

// PURPOSE: Bubbles up the node to correct position in the tree using recursion.
// PARAMETER: index = node at index to bubble up.
void MinHeap::bubbleUp(int index) 
{
	//if index is at 0, no need to bubble up.
	if (index == 0) {
		return;
	}

	// parents of node at index
	auto parentIndex = (index - 1) / 2;				

	// if node at [parentindex] is greater than node at[index]
	if (data[parentIndex]->priority > data[index]->priority) {

		//swap places [parentindex] and [index] by...
		auto * temp = data[parentIndex];			// temp variable to hold value at index
		data[parentIndex] = data[index];			// set parentindex to index.
		data[index] = temp;							// then restore parentindex to index.

		bubbleUp(parentIndex);						// then check if parent index is in the correct position recursively.
	}
}

// PURPOSE: Inserts new value into heap.
// PARAMETER: newValue = the new value to insert into heap.
void MinHeap::insert(PCB& value) 
{
	data.emplace_back(&value);						// adding new value to the end of data.
	++size;											// size of heap incremented.

	bubbleUp(data.size() - 1);						// bubbling up the last node in the tree to correct position.
}


// PURPOSE: Deletes the min value at root.
void MinHeap::deleteMin()
{
	// if vector is empty, nothing needs to be done, so return.
	if (data.empty()) {
		return;
	}

	// else, if vector is not empty...
	data[0] = data.back();							// set root to last node
	data.pop_back();								// delete last node.
	--size;											// size of heap decremented.

	bubbleDown(0);
}


// PURPOSE: Returns smallest value from the root.
PCB* MinHeap::getMin() 
{
	return data[0];	 // value at root.
}

// PURPOSE: Returns the size of the heap.
int MinHeap::getSize()
{
	return size;
}

// PURPOSE: Displays the contents of the minimum heap.
void MinHeap::display()
{
	std::cout << "--------------------------------------------------------\n";
	std::cout << std::left << std::setw(5) << "ID " << std::setw(11) << "Priority " << std::setw(13) << "State " << std::setw(15) << "Address" << "Size = " << size << "\n";
	std::cout << "--------------------------------------------------------\n";
	
	// case 1: list is empty.
	if (data.empty()) {
		std::cout << "empty\n";
	}

	// case 2: list is not empty.
	// Bcause of how minimum heaps are structured, in which each node abides to the heap property,
	// displaying the heap as an indexed array list will not display the contents in ascending order.
	for(auto i = 0; i < data.size(); ++i) {
		std::cout << std::left << std::setw(8) << data[i]->ID << std::setw(8) << data[i]->priority << std::setw(13) << pcbStates::enumList[data[i]->state] << std::setw(10) << data[i] << "\n";
	}

	std::cout << "\n\n";
}
