/*
 * Filename:	encodeInput.c
 * Project:	    A-02 : WRITING A LINUX UTILITY
 * By:	    	Hoang Phuc Tran - ID: 8789102
				Caine Phung - ID: 6983324
 * Date:		January 29, 2022
 * Description: This application encodes input files and stdin to stdout or The S-RECORD / ASM files
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../inc/assembly.h"
#include "../inc/s_record.h"


#pragma warning(disable : 4996)

int main(int argc, char* argv[]) {

	char* first = argv[1];
	char* second = argv[2];
	char* third = argv[3];
	char* outputFile = { 0 };
	char* inputFile = { 0 };
	char* outExt = { 0 };
	bool srec = false;
	bool input = false;
	bool output = false;

	//initial check for "-srec"
	for (int i = 1; i < argc; i++) {

		if (strcmp(argv[i], "-srec") == 0) {
			srec = true;
			break;
		}
	}

	//switch case for argv
	switch (argc) {

	case 1:

		//read std, write stdout
		asmEncode_in_out();
		break;

	case 2:

		if ((strcmp(argv[1], "-srec") != 0) && (first[0] == '-')) {

			switch (first[1]) {

			case 'i':
				input = true;
				inputFile = strchr(first, 'i') + 1;
				break;

			case 'o':
				output = true;
				outputFile = strchr(first, 'o') + 1;
				break;
			
			// show usage statement
			case 'h':
				printf("encodeIput and its allowable runtime switches\n");
				printf("encodeInput [-i<<InputFile>>] [-o<<OutputFile>>] [-srec]\n");
				printf("Switches can be placed in any order.\n");
				break;

			default:
				break;
			}
		}
		break;

	case 3:

		if ((strcmp(argv[1], "-srec") != 0) && (first[0] == '-')) {

			switch (first[1]) {

			case 'i':
				input = true;
				inputFile = strchr(first, 'i') + 1;
				break;

			case 'o':
				output = true;
				outputFile = strchr(first, 'o') + 1;
				break;

			default:
				break;
			}
		}

		if ((strcmp(argv[2], "-srec") != 0) && (second[0] == '-')) {

			switch (second[1]) {

			case 'i':
				input = true;
				inputFile = strchr(second, 'i') + 1;
				break;

			case 'o':
				output = true;
				outputFile = strchr(second, 'o') + 1;
				break;

			default:
				break;
			}
		}

		break;

	case 4:

		if ((strcmp(argv[1], "-srec") != 0) && (first[0] == '-')) {

			switch (first[1]) {

			case 'i':
				input = true;
				inputFile = strchr(first, 'i') +1;
				break;

			case 'o':
				output = true;
				outputFile = strchr(first, 'o') + 1;
				break;

			default:
				break;
			}
		}

		if ((strcmp(argv[2], "-srec") != 0) && (second[0] == '-')) {

			switch (second[1]) {

			case 'i':
				input = true;
				inputFile = strchr(second, 'i') + 1;
				break;

			case 'o':
				output = true;
				outputFile = strchr(second, 'o') + 1;
				break;

			default:
				break;
			}
		}

		if ((strcmp(argv[3], "-srec") != 0) && (third[0] == '-')) {

			switch (third[1]) {

			case 'i':
				input = true;
				inputFile = strchr(third, 'i') + 1;
				break;

			case 'o':
				output = true;
				outputFile = strchr(third, 'o') + 1;
				break;

			default:
				break;
			}
		}

		break;

	default:
		printf("Too many arguments!");
		break;
	}

	//parsing output file's extension
	if (outputFile != NULL) {
		outExt = strchr(outputFile, '.');
	}

	//input file, output file, no srec switch
	if (input == true && output == true && srec == false) {

		if (outExt != NULL) {

			if (strcmp(outExt, ".asm") == 0) {
				asmEncode(inputFile, outputFile);	
			}

			else if (strcmp(outExt, ".serc") == 0) {
				inputFileToSrecFile(inputFile, outputFile);
			}

			else{
				char fileName[20] = "";
				strcpy(fileName, outputFile);
				strcat(fileName, ".asm");
				asmEncode(inputFile, fileName);
			}		
		}
	}

	//output file, no input file, no srec switch

	if (input == false && output == true && srec == false) {

		if (outExt != NULL) {

			if (strcmp(outExt, ".asm") == 0) {
				asmEncode_in(outputFile);
			}

			else if (strcmp(outExt, ".srec") == 0) {
				stdinToSrecFile(outputFile);
			}

			else {
				char fileName[20] = "";
				strcpy(fileName, outputFile);
				strcat(fileName, ".asm");
				asmEncode_in(fileName);
			}
		}
	}

	//output file, srec switch, no input file
	if (input == false && output == true && srec == true) {

		if (outExt != NULL) {

			if (strcmp(outExt, ".srec") == 0) {
				stdinToSrecFile(outputFile);
			}

			else {
				char fileName[20] = "";
				strcpy(fileName, outputFile);
				strcat(fileName, ".srec");
				stdinToSrecFile(fileName);
			}
		}
	}

	//input file, srec switch, output file
	if (input == true && output == true && srec == true) {

		if (outExt != NULL) {

			if (strcmp(outExt, ".srec") == 0) {
				inputFileToSrecFile(inputFile,outputFile);
			}

			else {
				char fileName[20] = "";
				strcpy(fileName, outputFile);
				strcat(fileName, ".srec");
				inputFileToSrecFile(inputFile,fileName);
			}
		}
	}

	//input file, no output file
	if (input == true && output == false) {

		// srec switch
		if(srec == true){
			char fileName[20] = "";
			strcpy(fileName, inputFile);
			strcat(fileName, ".srec");
			inputFileToSrecFile(inputFile, fileName);
		}
		
		 // no srec switch
		else {
				char fileName[20] = "";
				strcpy(fileName, inputFile);
				strcat(fileName, ".asm");
				asmEncode(inputFile, fileName);		
		}
	}
}
