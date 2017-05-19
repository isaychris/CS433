// ============================================
// Name: Chris Banci
// Assignment: 3 - CPU Scheduling
// File type: driver file
// ============================================
#include <iostream>
#include <string>
#include "simulation.h"
using namespace std;

// function prototypes
void handleArgs(Simulation &DES, int argc, char * argv[]);
void prompt(Simulation &DES, int argc, char * argv[]);

// PURPOSE: Tests the implementation of CPU schedulers using Discrete Event Simulator
// PARAMETERS: argc = number of arguments
//			   argv[] = arguments passed
int main(int argc, char * argv[])
{
	cout << "// Name: Chris Banci" << endl;
	cout << "// Date : March 27, 2017" << endl;
	cout << "// Course : CS433 - Operating Systems" << endl;
	cout << "// Assignment : 3 - CPU scheduling" << endl;
	cout << "---------------------------------------------------------" << endl << endl;

	Simulation DES;

	handleArgs(DES, argc, argv);	
	DES.setup();					

	switch (DES.selection) {
	case 1: // FCFS Scheduler
		DES.runFCFS();
		cout << "Generating FCFS Statistics ..." << endl << endl;
		DES.report();
		break;
	case 2: // SJF Scheduler
		DES.runSJF();
		cout << "Generating SJF Statistics ..." << endl << endl;
		DES.report();
		break;
	}

	return 0;
}

// PURPOSE: If user does not pass parameters through commandline, the program will prompt for input.
//			If user does pass parameters through commandline and it is invalid, the program will display error and prompt for input.
// PARAMETERS: &DES = DES Simulation
//			   argc = number of arguments
//			   argv[] = arguments passed
void handleArgs(Simulation &DES, int argc, char * argv[])
{
	// if 2 arguments are passed
	if (argc == 3) {
		DES.amount = atoi(argv[1]);
		DES.selection = atoi(argv[2]);

		// input error handling
		if (DES.amount < 1 || DES.selection < 1 || DES.selection > 2) {
			cout << "[Error] Invalid argument(s) ..." << endl;
			prompt(DES, argc, argv);
		}
	}

	// if 2 arguments are not passed
	else {

		// input error handling
		if (argc > 3 || argc == 2) {
			cout << "[Error] Invalid argument(s) ..." << endl;
		}

		prompt(DES, argc, argv);
	}
}


// PURPOSE: prompts user for input, such as how many processes to place into simulation and which cpu scheduler to use.
// PARAMETERS: &DES = DES simulation
//			   argc = number of arguments
//			   argv[] = arguments passed
void prompt(Simulation &DES, int argc, char * argv[]) {
	cout << "Enter number of processes to add into DES Simulation: ";
	cin >> DES.amount;

	// input error handling
	while (DES.amount < 1 || cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "[Error] enter again: ";
		cin >> DES.amount;
	}
	cout << endl;

	cout << "Select scheduler type" << endl;
	cout << "1: FCFS" << endl;
	cout << "2: SJF" << endl << endl;

	cout << ">> ";
	cin >> DES.selection;

	// input error handling
	while (DES.selection < 1 || DES.selection > 2 || cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "[Error] enter again: ";
		cin >> DES.selection;
	}
	cout << endl;
}