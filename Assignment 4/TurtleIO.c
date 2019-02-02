/************************
 * Purpose: This file contains the IO and validation for the UCP assignment
 * Author: Aaron Gangemi (19447337)
 * Date Modified: 18 October 2018
 * ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TurtleIO.h"
#include "TurtleGraphics.h"
#include "LinkedList.h"
#include "effects.h"
/*Purpose: Reads in the lines, executes validating functions and
 *         Passes value into the linked list. 
 * parameters: filename
 * return: none 
 * */         
void readLines(char* fileName, LinkedList* list)
{
    int noOfElements, processLine;   /*Initialise Variables*/
    newString line;
    FILE* inputFile = NULL;
    inputFile = fopen(fileName, "r");
    if(inputFile == NULL) /*Check if file exists*/
    {
        printf("Error, could not open input file");
    } /*Will exit gracefully if file doesn't exist*/
    else  
    {
        noOfElements = fscanf(inputFile, "%7s %4s", (line).newCommand, 
                              (line).newValue); /*noOfElements is the number
                                               of successfully read values*/ 
        checkEmptyLine(noOfElements);   /*Checks if file is empty*/
        while(noOfElements != EOF)   /*continue until file is at end*/
        {
            convertToLowercase(line.newCommand); /*convert all values to 
                                                    lowercase so file is valid
                                                    */
            processLine = validateDataType(line.newCommand, line.newValue);
            /*Checks the data type is valid. returns an integer as a bool value
                and skips the line if the data type is invalid*/              
            checkNoOfElements(noOfElements, (line).newCommand, (line).newValue,
                              inputFile);
            if(processLine == boolTrue)   
            {
                insertLast(line, list);
            }
            noOfElements = fscanf(inputFile, "%s %s", line.newCommand, line.newValue);
            /*read in the next line*/
        }  
        fclose(inputFile); /*close the file*/
   }
}

/******************************
 * Reference: https://codescracker.com/c/program/c-program-convert-uppercase-
 *            into-lowercase.htm
 * NOTE: NO AUTHOR WAS STATED ON LINK
 * Purpose: To convert each line to lowercase using ascii character. Relates
 *          to IO Function by ensuring command is not invalid due to 
 *          uppercase or lowercase
 * Imports: command[]
 * Export: NONE
 * *************************/
void convertToLowercase(char command[])
{
    /*Obtained code https://codescracker.com/c/program/c-progra
                    m-convert-uppercase-into-lowercase.htm*/
    /*No author stated*/
    /*Accessed 14 October 2018*/
    int i;
    for(i = 0; i < strlen(command); i++)
    {
        if(command[i] >= 65 && command[i] <= 92)  /*check for uppercase*/
        {
            command[i] = command[i] + 32;  /*convert to lowercase*/
        }
    }
    /*End of code obtained from: https://codescracker.com/c/program/c-progra
                                 m-convert-uppercase-into-lowercase.htm */
}

/*****************************
 * Purpose: To check if the file is empty. This is a validation method used
 *          in the IO method
 * Import: noOfElements
 * Export: None
 * *************************/
void checkEmptyLine(int noOfElements)
{
    if(noOfElements == -1)  /*if noOfElements read in is -1, then line doesn't 
                            exist*/
    {
        printf("There are no lines in file, please re-enter the filename\n");
    }
}

/********************************
 * Purpose: check the file contents(command and value) are read in successfully.
 *          This is a IO validation method used in the read in method.
 * Import: noOfElements, command, value, inputFile
 * Export: noOfElements
 * ****************************/
int checkNoOfElements(int noOfElements, char* command, char* value, 
                      FILE* inputFile)
{
    if(noOfElements != 2) /*If file has more than 1 parameter after command*/
    {
        printf("file contains invalid line, stop drawing here. EOF");   
        noOfElements = EOF; 
    }
    return noOfElements;
}

/***************************
 * Purpose: validate the command and value are of the correct datatype. 
 *          This is a IO validation method used in the read lines method
 * Import: command, value
 * Export: success (Boolean)
 * */
int validateDataType(char* command, char* value)
{
    int convertedValue;
    int success = boolTrue;
    if(((strcmp(command, "pattern")!=0)) && (strcmp(command, "bg")!= 0)
        && (strcmp(command, "fg") != 0)) /*if not pattern*/
    {
        convertedValue = atoi(value); /*convert ito an integer*/
        if(convertedValue == 0) /*if unable to convert to integer*/
        {
            convertedValue = atol(value); /*try convert to double*/
            if(convertedValue == 0) /*if unable to convert to double*/
            {
                success = boolFalse;
                printf("Invalid datatype found in file ");
                printf("or incorrect command found\n");
            }
        }        
    }  
    return success;
}
/*************************
 * Purpose: to convert the linked list value to a double. This is used in 
 *          the else statement for the commands to convert certain values
 *          to doubles. In addition, it is used for validation to check
 *          a value is of the correct datatype.
 * Import: value
 * Export: newValue
 * ********************/
double convertDouble(char* value)
{
    double newValue = atol(value);
    return newValue;
}
/************************
 * Purpose: to convert the linked list value to an integer. This method
 *          is used in the else statement to convert a value from string to 
 *          int
 * Import: value
 * Export: newValue
 * ***********************/
int convertInt(char* value)
{
    int newValue = atoi(value);
    return newValue;
} 

