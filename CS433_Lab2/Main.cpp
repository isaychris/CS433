// ============================================
// Name: Chris Banci
// Assignment: 2 - UNIX Shell and History Feature
// Compiler: g++
// File type: Driver file
// ============================================
#include <cstring>
#include <iostream>
#include "Shell.h"

// PURPOSE: A driver to test out the implementation of shell.
//	    The command entered is first parsed then check if it is a user or shell command.
//      if user command, it is executed through execUserCommand().
//	    if shell command, it is saved and exected through execShellCommand().
int main() {
	Shell osh;

	while (osh.running) {
		char buffer[MAXLINE];					// command buffer
		char buffer_save[MAXLINE];				// used to save the command
		char * args[MAXLINE / 2 + 1];			// arguments of the command.

		std::cout << "osh> ";
		std::cout.flush();

		std::cin.getline(buffer, MAXLINE);		// reads command from input.		
		strcpy(buffer_save, buffer);			// copy the buffer

		osh.parseline(buffer, args);			// buffer parses into arguments.

		if (osh.isUserCommand(args)) {
			osh.execUserCommand(args);			// command is user command.
		}

		else {
			osh.saveCommand(buffer_save);		// save command if shell command.
			osh.execShellCommand(args);			// command is shell command.
		}
	}

	return 0;
}