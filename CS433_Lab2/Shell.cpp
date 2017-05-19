// ============================================
// Name: Chris Banci
// Assignment: 2 - UNIX Shell and History Feature
// Compiler: g++
// File type: Shell implementation file
// ============================================
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include "Shell.h"

using namespace std;

// PURPOSE: This function displays the command history list.
void Shell::displayHistory()
{
	// history is empty
	if (history.empty()) {
		cout << "command history is empty" << endl;
	}

	// history not empty
	else {
		int start = (history.size() < 10) ? 0 : history.size() - 10;

		// display history
		for (int i = start; i < history.size(); i++) {
			cout << "  " << i + 1 << "  " << history[i] << endl;
		}
	}
}

// PURPOSE: This function executes a user command.
// PARAMETER: arg[] = arguments of the command.
void Shell::execUserCommand(char* arg[])
{
	string command(arg[0]);

	// command to exit out of program
	if (command == "exit") {
		running = false;
	}

	// command to display command history
	else if (command == "history") {
		displayHistory();
	}

	// command used to select a previous command in command history
	else if (command[0] == '!') {
		char buffer[MAXLINE];
		char * args[MAXLINE / 2 + 1];
		int N;	

		// command is "!!" format, selects the most recent command
		if (command == "!!") {

			// input error
			if (history.empty()) {
				cout << "No commands in history." << endl;
				return;
			}

			N = history.size();
		}

		// command is "!N" format, selects the Nth command.
		else {

			// seperate ! and N
			string temp = command.substr(1, command.length());			
			N = atoi(temp.c_str());	// converts string to int.

			// last command to show
			int min = (history.size() < 10) ? 0 : history.size() - 10;

			// input error handling
			if (N > history.size() || N < min + 1) {
				cout << "No such command in history." << endl;
				return;
			}
		}
		// echo selected command to screen.
		cout << history[N - 1] << endl; 

		// copy command into a buffer, so it can be parsed and executed
		strcpy(buffer, history[N - 1].c_str());
		saveCommand(buffer);
		parseline(buffer, args);
		execShellCommand(args);
	}
}

// PURPOSE: This function checks if the command entered is a user command or execShellCommand command.
// PARAMETER: arg[] = the arguments in the command.
// RETURN: true = if user command.
//	   false = if shell command.
bool Shell::isUserCommand(char * arg[])
{
	string command(arg[0]);

	// command is a user command
	if (command == "exit" || command == "history" || command[0] == '!') {
		return true;
	}

	// command is a shell command
	return false;
}

// PURPOSE: This function saves a command into history.
// PARAMETER: command[] = the command to save.
void Shell::saveCommand(char command[])
{
	string save(command);
	history.push_back(save);
}


// PURPOSE: This function parses the buffer into arguments.
// PARAMETERS: buffer[] = the command.
//		 args[] = the arguments in the command.
void Shell::parseline(char buffer[], char * args[])
{
	int i = 0;

	// buffer tokenized using loop
	char * p = strtok(buffer, " ");

	while (p != NULL) {
		args[i] = p;
		p = strtok(NULL, " ");
		i++;
	}

	// if command has ampersand at the end of argument list, remove it and null terminate
	if (strcmp(args[i - 1], "&") == 0) {
		args[i - 1] = NULL;
		ampersand = true;
	}

	else {
		// terminated argument list with null
		args[i] = NULL;
		ampersand = false;
	}
}

// PURPOSE: This function executes a shell command.
// PARAMETER: args[] = the arguments in the command.
void Shell::execShellCommand(char * args[])
{
	/*
	* After reading user input, the steps are:
	* (1) fork a child process using fork()
	* (2) the child process will invoke execvp()
	* (3) if command not included &, parent will invoke wait()
	*/

	pid_t pid = fork();			// step 1

	// child process
	if (pid == 0) {
		execvp(args[0], args);	// step 2
	
		cout << "execvp: command not found" << endl;
		exit(1); 		
	}

	// parent process
	else if (pid > 0) {
		if (ampersand == false) {
			wait(NULL);			// step 3
		}
	}

	// fork failed
	else {
		cout << "fork: failed to fork process" << endl;
		exit(1);
	}
}


// Default constructor for shell.
Shell::Shell()
{
	running = true;
	ampersand = false;
}
