/*Guard to ensure files are not duplicated*/
#ifndef TURTLEIO_H
/*Guard to ensure files are not duplicated*/
#define TURTLEIO_H
#include "LinkedList.h"
/*The below values are boolean values, represented as integers.
 * used to indicate whether a line is valid in read lines method
 */
#define boolTrue 1
#define boolFalse 0

/* Purpose: Reads in the lines, executes validating functions and
 * Passes value into the linked list. 
 */
void readLines(char* fileName, LinkedList* list);


/* To convert each line to lowercase using ascii character. Relates
 * to IO Function by ensuring command is not invalid due to 
 * uppercase or lowercase
 */
void convertToLowercase(char command[]);


/* To check if the file is empty. This is a validation method used
 * in the IO method
 */
void checkEmptyLine(int noOfElements);


/* check the file contents(command and value) are read in successfully.
 * This is a IO validation method used in the read in method.
 */
int checkNoOfElements(int noOfElements, char* command, char* value,
                       FILE* inputFile);


 /* validate the command and value are of the correct datatype. 
  * This is a IO validation method used in the read lines method
  */
int validateDataType(char* command,char* value);


/* to convert the linked list value to a double. This is used in 
 * the else statement for the commands to convert certain values
 * to doubles. In addition, it is used for validation to check
 * a value is of the correct datatype.
 */
double convertDouble(char* value);

/* Purpose: to convert the linked list value to an integer. This method
 * is used in the else statement to convert a value from string to 
 * int
 */
int convertInt(char* value);
#endif

