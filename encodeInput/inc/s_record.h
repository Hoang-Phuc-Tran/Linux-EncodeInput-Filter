/*
 * Filename:	s_record.h
 * Project:	    A-02 : WRITING A LINUX UTILITY
 * By:	    	Hoang Phuc Tran - ID: 8789102 
				Caine Phung - ID: 6983324
 * Date:		January 29, 2022
 * Description: This file contains prototypes and header files.
 */

#include <stdio.h>
#include <string.h>

int stdinToSrecStdout();
int stdinToSrecFile(char* outputFile);
int inputFileToSrecFile(char* inputFile, char* outputFile);
