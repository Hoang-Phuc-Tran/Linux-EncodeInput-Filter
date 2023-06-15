/*
 * Filename:	s_record.c
 * Project:	    A-02 : WRITING A LINUX UTILITY
 * By:	    	Hoang Phuc Tran - ID: 8789102
				Caine Phung - ID: 6983324
 * Date:		January 29, 2022
 * Description: The functions in this file are used to encode a file and stdin to stdout or The ASSEMBLY files
 */


#include <string.h>
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define outputLine 17
#pragma warning(disable : 4996)

 /*
 * METHOD : asmEncode
 * DESCRIPTION : encode files in asm format
 * PARAMETERS : char* input, char* output
 */

int asmEncode(char* input, char* output){


	FILE* fp = NULL;
	FILE* fp2 = NULL;
	char	record[outputLine] = { 0 };
	int i = 0;

	/* open file to read */
	fp = fopen(input, "r");

	/* error handling */
	if (fp == NULL)
	{
		printf("Can't open TEXT file for reading.\n");
		return -1;
	}

	

	/* open file to write */
	fp2 = fopen(output, "w");

	/* error handling */
	if (!fp2) {

		printf("Unable to open the writing!\n");
		return -2;
	}

	/* reading each line until EOF is reached */
	while (fgets(record, sizeof record, fp) != 0)
	{
		fprintf(fp2, "dc.b	");


		/* iterate through each line */
		for (int i = 0; i < strlen(record); i++)
		{

			if (record[i] != '\n') {
				if ((record[i + 1] == '\n') || (record[i + 1] == '\0')) {
					fprintf(fp2, "$%02X", record[i]);
				}

				else {
					fprintf(fp2, "$%02X,", record[i]);
				}
			}
		}
		fprintf(fp2, "\n");
	}


	/* error handling */
	if (feof(fp))
	{
		return 0;
	}
	else
	{
		/* error handling */
		if (ferror(fp))
		{

			printf("Error reading a record from the file\n");

			if (fclose(fp) != 0)
			{

				printf("Can't close the TEXT file we opened for reading\n");
			}
			return -3;
		}
	}

	/* error handling */
	if (fclose(fp) != 0)
	{
		// can't close it 
		printf("Can't close file we opened for reading\n");
		return -4;
	}

	/* error handling */
	if (fclose(fp2) != 0)
	{
		// can't close it 
		printf("Can't close file we opened for reading\n");
		return -5;
	}

	return 0;
}




/*
* METHOD : asmEncode_in
* DESCRIPTION : encode files in asm format using stdin
* PARAMETERS : char* output
*/

int asmEncode_in(char* output) {


	
	FILE* fp = NULL;
	char	record[outputLine] = { 0 };
	int i = 0;

	/* open file to read */
	// Get input from sdtin
	

	/* open file to write */
	fp = fopen(output, "w");

	/* error handling */
	if (!fp) {

		printf("Unable to open the writing!\n");
		return -2;
	}

	/* reading each line until EOF is reached */
	while (fgets(record, sizeof record, stdin) != 0)
	{
		fprintf(fp, "dc.b	");
		

		/* iterate through each line */
		for (int i = 0; i < strlen(record); i++)
		{

			if (record[i] !=  '\n') {
				if ((record[i + 1] == '\n') || (record[i + 1] == '\0')) {
					fprintf(fp, "$%02X", record[i]);
				}

				else {
					fprintf(fp, "$%02X,", record[i]);
				}
			}
		}
		fprintf(fp, "\n");
	}

	/* error handling */
	if (feof(fp))
	{
		return 0;
	}
	else
	{
		/* error handling */
		if (ferror(fp))
		{

			printf("Error reading a record from the file\n");

			if (fclose(fp) != 0)
			{

				printf("Can't close the TEXT file we opened for reading\n");
			}
			return -3;
		}
	}

	/* error handling */
	if (fclose(fp) != 0)
	{
		// can't close it 
		printf("Can't close file we opened for reading\n");
		return -4;
	}

	/* error handling */
	

	return 0;
}



/*
* METHOD : asmEncode_in_out
* DESCRIPTION : encode in asm format using stdin and stdout
* PARAMETERS : void
*/
int asmEncode_in_out(void) {
	
	char	record[outputLine] = { 0 };
	int i = 0;

	
	while (fgets(record, sizeof record, stdin) != 0)
	{
		fprintf(stdout, "dc.b	");


		/* iterate through each line */
		for (int i = 0; i < strlen(record); i++)
		{

			if (record[i] != '\n') {
				if ((record[i + 1] == '\n') || (record[i + 1] == '\0')) {
					fprintf(stdout, "$%02X", record[i]);
				}

				else {
					fprintf(stdout, "$%02X,", record[i]);
				}
			}
		}
		fprintf(stdout, "\n");
	}

	return 0;
}

