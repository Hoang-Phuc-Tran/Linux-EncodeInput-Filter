/*
 * Filename:	s_record.c
 * Project:	    A-02 : WRITING A LINUX UTILITY
 * By:	    	Hoang Phuc Tran - ID: 8789102
				Caine Phung - ID: 6983324
 * Date:		January 29, 2022
 * Description: The functions in this file are used to encode a file and stdin to stdout or The S-RECORD files
 */

#include <stdio.h>
#include <string.h>

#pragma warning(disable:4996) 

// Constants
#define CHECKSUM_BYTE 1
#define COUNT_ADDRESS_BYTE 2
#define MAX_HEXIMAL 10
#define MAX_COUNT_FIELD 20
#define MAX_COUNT 16
#define ADDRESS_BYTE 5


// Prototype
int printCountHeximalByte(FILE* output, int count);


 /*
 * Function: inputFileToSrecFile()
 * Description:  This function will encode an input file to SREC file
 * Parameters:  char * inputFile  -	Input File
 *				char * outputFile - Output File
 * Returns: int (0 indicates successful, otherwise fail)
 */
int inputFileToSrecFile(char* inputFile, char* outputFile)
{
	// Declare pointer FILEs
	FILE* input;
	FILE* output;

	char arrayToSrec[MAX_COUNT_FIELD] = { 0 };
	char name[] = "PHUC-CAiNE";
	char* ptr = NULL;
	int counter = 0;
	char heximalNumber[MAX_HEXIMAL] = { 0 };
	char address[ADDRESS_BYTE] = { 0 };
	unsigned int ch = 0;
	unsigned char checksum = 0;
	int addressByte = 0;
	int countSrec = 0;

	// Open file to read
	input = fopen(inputFile, "r");

	// Open file to write
	output = fopen(outputFile, "w");

	if (input == NULL)
	{
		printf("ERROR: Can't open file to read!\n");
		return -1;
	}
	else if (output == NULL)
	{
		printf("ERROR: Can't open file to write!\n");
		return -1;
	}
	else
	{

		// S0 type record
		fputs("S0", output);
		
		int i = 0;

		// loop name
		while (name[i] != '\0')
		{
			// Count characters of a string
			counter++;

			// Calculate the sum of DATA field’s values
			checksum = checksum + name[i];

			i++;
		}

		// add 2 for address byte and add 1 for checksum byte
		counter = counter + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE;

		// he sum of the COUNT, ADDRESSand DATA fields of the record
		checksum = checksum + counter;

		// Calculate the 1’s Complement value and strip off  the value in the least significant byte
		checksum = ~checksum & 0xff;

		printCountHeximalByte(output, counter);

		fputs("0000", output);

		i = 0;

		// Loop the string name
		while (name[i] != '\0')
		{
			// Convert to 2 heximal number
			sprintf(heximalNumber, "%02X", name[i]);

			// Write to file
			fputs(heximalNumber, output);

			i++;
		}

		// Convert to 2 heximal number
		sprintf(heximalNumber, "%02X", checksum);

		// Write to file
		fputs(heximalNumber, output);

		// reset check sum and counter 
		counter = 0;

		ch = fgetc(input);

		// Read from a file
		while (ch != EOF)
		{
			// Put a character to array
			arrayToSrec[counter] = ch;
			counter++;

			if (counter == MAX_COUNT)
			{
				fputs("\nS1", output);

				// Write 2 characters representing a single hexadecimal byte
				printCountHeximalByte(output, (counter - COUNT_ADDRESS_BYTE - CHECKSUM_BYTE));

				// convert address to heximal
				sprintf(address, "%04X", addressByte);

				// Write 4 characters representing a hexadecimal addres to a file
				fputs(address, output);

				counter = 0;
				checksum = 0;

				// Write characters to file
				while (counter < MAX_COUNT)
				{
					// convert to heximal
					sprintf(heximalNumber, "%02X", arrayToSrec[counter]);

					// Write to file
					fputs(heximalNumber, output);

					// Calculate checksum
					checksum = checksum + arrayToSrec[counter];

					counter++;
				}

				// Calculate final checksum
				checksum = checksum + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE + MAX_COUNT_FIELD + addressByte;

				// Calculate the 1’s Complement value and strip off  the value in the least significant byte
				checksum = ~checksum & 0xff;

				// Convert to heximal 
				sprintf(heximalNumber, "%02X", checksum);

				// Write to file
				fputs(heximalNumber, output);

				counter = 0;
			}

			ch = fgetc(input);

			// Increase address byte
			addressByte = addressByte + MAX_COUNT_FIELD;
		}

		if (counter > 0)
		{
			int i = 0;

			fputs("\nS1", output);

			// convert to heximal
			sprintf(heximalNumber, "%02d", (counter + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE));

			// Write to file
			fputs(heximalNumber, output);

			// convert address to heximal
			sprintf(address, "%04X", addressByte);

			// Write 4 characters representing a hexadecimal addres to a file
			fputs(address, output);

			while (i < counter)
			{
				// convert to heximal
				sprintf(heximalNumber, "%02X", arrayToSrec[i]);

				// Write to file
				fputs(heximalNumber, output);

				// Calculate checksum
				checksum = checksum + arrayToSrec[i];

				i++;

			}
			// Calculate final checksum
			checksum = checksum + counter + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE + addressByte;

			// Calculate the 1’s Complement value and strip off  the value in the least significant byte
			checksum = ~checksum & 0xff;

			// Convert to heximal 
			sprintf(heximalNumber, "%02X", checksum);

			// Write to file
			fputs(heximalNumber, output);

			addressByte = addressByte + counter;

		}
		fputs("\nS503", output);

		// convert address to heximal
		sprintf(address, "%04X", addressByte);

		// Write 4 characters representing a hexadecimal addres to a file
		fputs(address, output);

		checksum = checksum + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE;
		// Calculate the 1’s Complement value and strip off  the value in the least significant byte
		checksum = ~checksum & 0xff;
		// Convert to heximal 
		sprintf(heximalNumber, "%02X", checksum);

		// Write to file
		fputs(heximalNumber, output);

		addressByte = addressByte + 2;

		fputs("\nS9030000", output);

		checksum = COUNT_ADDRESS_BYTE + CHECKSUM_BYTE;
		// Calculate the 1’s Complement value and strip off  the value in the least significant byte
		checksum = ~checksum & 0xff;
		// Convert to heximal 
		sprintf(heximalNumber, "%02X", checksum);

		// Write to file
		fputs(heximalNumber, output);


		// Check errors 
		if (ferror(input))
		{
			printf("Error reading line from file");
			// If any errors occur, close the file
			if (fclose(input) != 0)
			{
				printf("Error closing the file\n");
				return -1;
			}
		}

		// Check errors 
		if (ferror(output))
		{
			printf("Error reading line from file");
			// If any errors occur, close the file
			if (fclose(output) != 0)
			{
				printf("Error closing the file\n");
				return -1;
			}
		}


	}
	return 0;
}



/*
 * Function: printCountHeximalByte()
 * Description:  This function will print 2 heximal numbers of count integer
 * Parameters:  char * inputFile  -	Input File
 *				int count
 * Returns: int (0 indicates successful, otherwise fail)
 */
int printCountHeximalByte(FILE* output, int count) {

	char arrayOutput[MAX_HEXIMAL] = { 0 };

	sprintf(arrayOutput, "%d", count);

	if (count > 9) 
	{
		fputc(arrayOutput[0], output);
		fputc(arrayOutput[1], output);			
		return 0;
	}
	else 
	{
		fputc('0', output);				
		fputc(arrayOutput[0], output);
		return 0;
	}

	return 0;
}


/*
 * Function: stdinToSrecFile()
 * Description:  This function will encode an input from stdin to SREC file
 * Parameters:  char * outputFile - Output File
 * Returns: int (0 indicates successful, otherwise fail)
 */
int stdinToSrecFile(char* outputFile)
{
	// Declare pointer FILEs
	FILE* output;

	char arrayToSrec[MAX_COUNT_FIELD] = { 0 };
	char name[] = "PHUC-CAINE";
	char* ptr = NULL;
	int counter = 0;
	char heximalNumber[MAX_HEXIMAL] = { 0 };
	char address[ADDRESS_BYTE] = { 0 };
	unsigned int ch = 0;
	unsigned char checksum = 0;
	int addressByte = 0;
	int countSrec = 0;

	// Open file to write
	output = fopen(outputFile, "w");

	if (output == NULL)
	{
		printf("ERROR: Can't open file to write!\n");
		return -1;
	}
	else
	{

		// S0 type record
		fputs("S0", output);

		int i = 0;

		// loop name
		while (name[i] != '\0')
		{
			// Count characters of a string
			counter++;

			// Calculate the sum of DATA field’s values
			checksum = checksum + name[i];

			i++;
		}

		// add 2 for address byte and add 1 for checksum byte
		counter = counter + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE;

		// he sum of the COUNT, ADDRESSand DATA fields of the record
		checksum = checksum + counter;

		// Calculate the 1’s Complement value and strip off  the value in the least significant byte
		checksum = ~checksum & 0xff;

		printCountHeximalByte(output, counter);

		fputs("0000", output);

		i = 0;

		// Loop the string name
		while (name[i] != '\0')
		{
			// Convert to 2 heximal number
			sprintf(heximalNumber, "%02X", name[i]);

			// Write to file
			fputs(heximalNumber, output);

			i++;
		}

		// Convert to 2 heximal number
		sprintf(heximalNumber, "%02X", checksum);

		// Write to file
		fputs(heximalNumber, output);

		// reset check sum and counter 
		counter = 0;

		// Get input from sdtin
		ch = fgetc(stdin);

		// Read from a file
		while (ch != EOF)
		{
			// Put a character to array
			arrayToSrec[counter] = ch;
			counter++;

			if (counter == MAX_COUNT)
			{
				fputs("\nS1", output);

				// Write 2 characters representing a single hexadecimal byte
				printCountHeximalByte(output, (counter - COUNT_ADDRESS_BYTE - CHECKSUM_BYTE));

				// convert address to heximal
				sprintf(address, "%04X", addressByte);

				// Write 4 characters representing a hexadecimal addres to a file
				fputs(address, output);

				counter = 0;
				checksum = 0;

				// Write characters to file
				while (counter < MAX_COUNT)
				{
					// convert to heximal
					sprintf(heximalNumber, "%02X", arrayToSrec[counter]);

					// Write to file
					fputs(heximalNumber, output);

					// Calculate checksum
					checksum = checksum + arrayToSrec[counter];

					counter++;
				}

				// Calculate final checksum
				checksum = checksum + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE + MAX_COUNT_FIELD + addressByte;

				// Calculate the 1’s Complement value and strip off  the value in the least significant byte
				checksum = ~checksum & 0xff;

				// Convert to heximal 
				sprintf(heximalNumber, "%02X", checksum);

				// Write to file
				fputs(heximalNumber, output);

				counter = 0;
			}

			// Get input from sdtin
			ch = fgetc(stdin);

			// Increase address byte
			addressByte = addressByte + MAX_COUNT_FIELD;
		}

		if (counter > 0)
		{
			int i = 0;

			fputs("\nS1", output);

			// convert to heximal
			sprintf(heximalNumber, "%02d", (counter + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE));

			// Write to file
			fputs(heximalNumber, output);

			// convert address to heximal
			sprintf(address, "%04X", addressByte);

			// Write 4 characters representing a hexadecimal addres to a file
			fputs(address, output);

			while (i < counter)
			{
				// convert to heximal
				sprintf(heximalNumber, "%02X", arrayToSrec[i]);

				// Write to file
				fputs(heximalNumber, output);

				// Calculate checksum
				checksum = checksum + arrayToSrec[i];

				i++;

			}
			// Calculate final checksum
			checksum = checksum + counter + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE + addressByte;

			// Calculate the 1’s Complement value and strip off  the value in the least significant byte
			checksum = ~checksum & 0xff;

			// Convert to heximal 
			sprintf(heximalNumber, "%02X", checksum);

			// Write to file
			fputs(heximalNumber, output);

			addressByte = addressByte + counter;

		}
		fputs("\nS503", output);

		// convert address to heximal
		sprintf(address, "%04X", addressByte);

		// Write 4 characters representing a hexadecimal addres to a file
		fputs(address, output);

		checksum = checksum + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE;
		// Calculate the 1’s Complement value and strip off  the value in the least significant byte
		checksum = ~checksum & 0xff;
		// Convert to heximal 
		sprintf(heximalNumber, "%02X", checksum);

		// Write to file
		fputs(heximalNumber, output);

		addressByte = addressByte + 2;

		fputs("\nS9030000", output);

		checksum = COUNT_ADDRESS_BYTE + CHECKSUM_BYTE;
		// Calculate the 1’s Complement value and strip off  the value in the least significant byte
		checksum = ~checksum & 0xff;
		// Convert to heximal 
		sprintf(heximalNumber, "%02X", checksum);

		// Write to file
		fputs(heximalNumber, output);


		// Check errors 
		if (ferror(output))
		{
			printf("Error reading line from file");
			// If any errors occur, close the file
			if (fclose(output) != 0)
			{
				printf("Error closing the file\n");
				return -1;
			}
		}


	}
	return 0;
}



/*
 * Function: stdinToSrecStdout()
 * Description:  This function will encode an input from stdin to stdout
 * Parameters:  NONE
 * Returns: int (0 indicates successful, otherwise fail)
 */
int stdinToSrecStdout()
{

	char arrayToSrec[MAX_COUNT_FIELD] = { 0 };
	char name[] = "PHUC-CANIE";
	char* ptr = NULL;
	int counter = 0;
	char heximalNumber[MAX_HEXIMAL] = { 0 };
	char address[ADDRESS_BYTE] = { 0 };
	unsigned int ch = 0;
	unsigned char checksum = 0;
	int addressByte = 0;
	int countSrec = 0;

	// Get input from stdin
	ch = fgetc(stdin);

		// write to stdout
		fputs("S0", stdout);

		int i = 0;

		// loop name
		while (name[i] != '\0')
		{
			// Count characters of a string
			counter++;

			// Calculate the sum of DATA field’s values
			checksum = checksum + name[i];

			i++;
		}

		// add 2 for address byte and add 1 for checksum byte
		counter = counter + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE;

		// he sum of the COUNT, ADDRESSand DATA fields of the record
		checksum = checksum + counter;

		// Calculate the 1’s Complement value and strip off  the value in the least significant byte
		checksum = ~checksum & 0xff;

		// write counter to stdout
		printCountHeximalByte(stdout, counter);

		fputs("0000", stdout);

		i = 0;

		// Loop the string name
		while (name[i] != '\0')
		{
			// Convert to 2 heximal number
			sprintf(heximalNumber, "%02X", name[i]);

			// Write to file
			fputs(heximalNumber, stdout);

			i++;
		}

		// Convert to 2 heximal number
		sprintf(heximalNumber, "%02X", checksum);

		// Write to stdout
		fputs(heximalNumber, stdout);

		// reset check sum and counter 
		counter = 0;

		// Read from a file
		while (ch != EOF)
		{
			if (ch == EOF)
			{
				break;
			}
			// Put a character to array
			arrayToSrec[counter] = ch;
			counter++;

			if (counter == MAX_COUNT)
			{
				fputs("\nS1", stdout);

				// Write 2 characters representing a single hexadecimal byte
				printCountHeximalByte(stdout, (counter - COUNT_ADDRESS_BYTE - CHECKSUM_BYTE));

				// convert address to heximal
				sprintf(address, "%04X", addressByte);

				// Write 4 characters representing a hexadecimal addres to a stdout
				fputs(address, stdout);

				counter = 0;
				checksum = 0;

				// Write characters to file
				while (counter < MAX_COUNT)
				{
					// convert to heximal
					sprintf(heximalNumber, "%02X", arrayToSrec[counter]);

					// Write to stdout
					fputs(heximalNumber, stdout);

					// Calculate checksum
					checksum = checksum + arrayToSrec[counter];

					counter++;
				}

				// Calculate final checksum
				checksum = checksum + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE + MAX_COUNT_FIELD + addressByte;

				// Calculate the 1’s Complement value and strip off  the value in the least significant byte
				checksum = ~checksum & 0xff;

				// Convert to heximal 
				sprintf(heximalNumber, "%02X", checksum);

				// Write to stdout
				fputs(heximalNumber, stdout);

				counter = 0;
			}
			ch = fgetc(stdin);

			// Increase address byte
			addressByte = addressByte + MAX_COUNT_FIELD;
		}

		if (counter > 0)
		{
			int i = 0;

			fputs("\nS1", stdout);

			// convert to heximal
			sprintf(heximalNumber, "%02d", (counter + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE));

			// Write to stdout
			fputs(heximalNumber, stdout);

			// convert address to heximal
			sprintf(address, "%04X", addressByte);

			// Write 4 characters representing a hexadecimal addres to a stdout
			fputs(address, stdout);

			while (i < counter)
			{
				// convert to heximal
				sprintf(heximalNumber, "%02X", arrayToSrec[i]);

				// Write to stdout
				fputs(heximalNumber, stdout);

				// Calculate checksum
				checksum = checksum + arrayToSrec[i];

				i++;

			}
			// Calculate final checksum
			checksum = checksum + counter + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE + addressByte;

			// Calculate the 1’s Complement value and strip off  the value in the least significant byte
			checksum = ~checksum & 0xff;

			// Convert to heximal 
			sprintf(heximalNumber, "%02X", checksum);

			// Write to stdout
			fputs(heximalNumber, stdout);

			addressByte = addressByte + counter;

		}
		fputs("\nS503", stdout);

		// convert address to heximal
		sprintf(address, "%04X", addressByte);

		// Write 4 characters representing a hexadecimal addres to a stdout
		fputs(address, stdout);

		checksum = checksum + COUNT_ADDRESS_BYTE + CHECKSUM_BYTE;
		// Calculate the 1’s Complement value and strip off  the value in the least significant byte
		checksum = ~checksum & 0xff;
		// Convert to heximal 
		sprintf(heximalNumber, "%02X", checksum);

		// Write to file
		fputs(heximalNumber, stdout);

		addressByte = addressByte + 2;

		fputs("\nS9030000", stdout);

		checksum = COUNT_ADDRESS_BYTE + CHECKSUM_BYTE;
		// Calculate the 1’s Complement value and strip off  the value in the least significant byte
		checksum = ~checksum & 0xff;
		// Convert to heximal 
		sprintf(heximalNumber, "%02X", checksum);

		// Write to stdout
		fputs(heximalNumber, stdout);



	
	return 0;
}

