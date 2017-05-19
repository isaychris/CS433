-----------------------------------
Name: Chris Banci
Date: February 9, 2017
Course: CS433 - Operating Systems
Assignment: 1
-----------------------------------


------------
Description:
------------
This program is an implementation of a priority queue of processes which contains two tests. The priority queue uses an implementation of the data structure min-heap.


In the first test,  the program tests the implementation of the priority queue by simulating insertion and deletion of processes in a CPU.


In the second test, the program tests the performance of the implementation by repeatedly moving processes in and out of the priority queue aka ReadyQueue.


---------------
Included Files:
---------------
     Source:
        Main.cpp              - contains the driver for the assignment
        ReadyQueue.cpp        - contains the data structure for the priority queue
        PCB.cpp               - contains the data structure of a Process Control Block
        PCB_Table.cpp         - contains the data structure for PCB Table.
        MinHeap.cpp           - contains the data structure used to implement ready queue.


    Headers:
	Main.h
	ReadyQueue.h
	PCB.h
	PCB_Table.h
	MinHeap.h


-----------
How to run:
-----------
To run this program, use the MakeFile which will compile the source files and create an executable called output.