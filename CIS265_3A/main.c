/*************************************************************************
* Title: (CIS265_3A) Decimal to Octal Conversion
* File: main.c
* Author: James Eli
* Date: 8/27/2017
*
* Write a program that reads an integer entered by the user and displays it 
* in octal (base 8):
*   Enter a number between 0 and 32767: 1953
*   In Octal, your number is: 03641
* The output should be displayed using 5 digits, even if fewer digits are 
* sufficient. Hint: To convert the number to octal, first divide it by 8; 
* the remainder is the last digit of the octal number (1, in this case). 
* Then divide the original number by 8 and repeat the process to arrive at 
* the next-to-last digit. (printf is capable of displaying numbers in base 
* 8, as we’ll see in Chapter 7, so there’s actually an easier way to write 
* this program).
*
* The program uses a recursive version of this decimal to octal conversion 
* algorithm:
*   int octal(int d) {
*     int remainder, n = 0;
*     while (d > 0) {
*       remainder = d % 8;
*       n = n*10 + remainder;
*       d /= 8;
*     }
*     return n;
*   }
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*  (2) Beware, the conversion function uses a recursive algorithm!
*  (3) Uses secure sscanf_s.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   08/27/2017: Initial release. JME
*************************************************************************/
#include <assert.h> 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions.
#define MIN_INPUT          0     // Maximum input value.
#define MAX_INPUT          32767 // Minimum input value.
#define MAX_INPUT_ATTEMPTS 3     // Maximum input attempts before aborting.

// Recursive decimal to octal conversion.
int octal(int n) {
	assert(n >= 0);
	if (n > 0)
		return octal(n / 8) * 10 + n % 8;
	return 0; 
}

// Program starts here.
int main(void) {
	int decimalNumber = 0;             // Number converted to octal.
	int attempts = MAX_INPUT_ATTEMPTS; // Input attempt counter.
	bool inputValid = false;           // Input validity flag, assumed bad (false).

	assert(attempts > 0); // Assert attempts valid non-zero, positive number.

	// Attempt only so many inputs.
	while (attempts--) {
		char input[7];  // Holds user input as string.
		int d;          // Temporary holds input number.

		// Prompt and grab user input.
		fputs("Enter a number between 0 and 32767: ", stdout);
		if (!fgets(input, sizeof input, stdin)) {
			fputs("\nFatal program error!\n", stderr);
			exit(EXIT_FAILURE);
		}
		else if (!strchr(input, '\n')) {
			// input too long, eat remaining characters.
			while (fgets(input, sizeof input, stdin) && !strchr(input, '\n'))
				; // Empty body.
			fputs("Too many characters input.\n", stdout);
		}
		else {
			// Catch special case of null input.
			if (strlen(input) <= 1)
				continue;
			// Attempt to convert from string to int, and validate.
			if (sscanf_s(input, "%d", &d)) {
				if (d >= MIN_INPUT && d <= MAX_INPUT) {
					decimalNumber = d;
					inputValid = true;
					break; // Exit.
				}
				else
					fprintf(stdout, "Value entered is outside allowable range (%d - %d)\n", MIN_INPUT, MAX_INPUT);
			}
			else
				fputs("Invalid input.\n", stdout);
		}
	}

	// If received valid input, convert decimalNumber to octal and display.
	if (inputValid)
		fprintf(stdout, "In Octal, your number is: %05d\n", octal(decimalNumber));
	else
		fputs("Try again.\n", stdout);
}
