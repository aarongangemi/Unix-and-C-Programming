#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "TurtleGraphics.h"
#include "TurtleIO.h"
#include "LinkedList.h"
#include "effects.h"
/* *Parts of this file comprise of externally-obtained code*
 * *Based on Curtin University Practicals and Lecture slides*
 * **********************************************************
 * Purpose: This is the TurtleGraphics file containing the main.
 * Author: Aaron Gangemi (19447337)
 * Date Modified: 12 October 2018
 */
int main(int argc, char* fileName[])
{
    LinkedListNode* currentNode;
    double xCoordinate = 0;
    double yCoordinate = 0;
    double currentAngle = 0;
    int foreground = 0;
    int background = 7;
    char pattern = '+';
    LinkedList* list = createList();
    char *command;
    char *value;
    FILE *appendFile;
    if(argc != 2) /*Validate number of args, if not 2 then file is invalid*/
    {
        printf("Incorrect amount of command line parameters");
    }
    else  /*FILE is VALID*/
    {
        appendFile = fopen("graphics.log","a"); /*Open log file*/
        fprintf(appendFile,"%s\n", "---"); /*Print dashes to log file*/
        readLines(fileName[1], list);  /*Reads lines in + validation*/
        clearScreen(); /*Clear screen - existing function*/
        setBgColour(background);
        setFgColour(foreground);
        currentNode = list->head;  /*Used for loop*/
        while(currentNode != NULL) /*WHILE NODES ARE IN LIST*/
        {
            command = ((newString*)(currentNode->data))->newCommand;
            value = ((newString*)currentNode->data)->newValue;
            /*Pass command and value to struct*/
            if(strcmp(command, "rotate") == 0)  /*CHECK FOR ROTATE*/
            {
                executeRotate(value, &currentAngle); /*CALL rotate function below*/
            }   
            else if(strcmp(command, "move") == 0)  /*CHECK FOR MOVE*/
            {
                fprintf(appendFile, "%s", command); /*append to file*/
                executeMove(value, &xCoordinate, &yCoordinate, currentAngle,
                             appendFile);
                /*CALL move function below*/
            }
            else if(strcmp(command, "draw") == 0) /*CHECK FOR DRAW*/
            {
                fprintf(appendFile, "%s", command); /*Append to file*/
                executeDraw(value, &xCoordinate, &yCoordinate, pattern, 
                            currentAngle, appendFile);
                /*CALL DRAW FUNCTION*/
            }
            else if(strcmp(command, "fg") == 0) /*CHECK FOR Foreground*/
            {
                executeFg(&foreground, value); /*CALL FG FUNCTION*/
            }
            else if(strcmp(command,"bg") == 0) /*Check for Background*/
            {
                executeBg(&background, value);
            }
            else if(strcmp(command,"pattern") == 0) /*check for pattern*/
            {
                executePattern(value, &pattern);
            }
            else /*If file doesn't exist*/
            {
                printf("Invalid file contents where data is %s %s\n", 
                        command, value); 
            }              
            currentNode = currentNode->next;
        }
        penDown();
        fclose(appendFile);
    }
    freeLinkedList(list);   /*Free list due to memory errors*/
    return 0;
}
 
/*
 * Purpose: The submodule below get the XCoordinate by multiplying the
 *          distance by cos(radeons). Returns the XCoordinate as integer.
 *          This is used in the execute commands to get X2
 * Import: distance, angle
 * Exportt: roundedX
 * */
int getXCoordinate(double distance, double angle)
{
    int roundedX = 0;
    double xCoordinate, radeons;
    radeons = (angle * PI)/180;
    xCoordinate = (distance) * cos(radeons);
    /*Obtained from chux*/
    /*https://stackoverflow.com/questions/2570934/how-to-round-
      floating-point-numbers-to-the-nearest-integer-in-c */ 
    /* (Accessed on October 7 2018)*/
    if(xCoordinate > 0)
    {
        roundedX = (int)(xCoordinate + 0.5);
    }
    else
    {
        roundedX = (int)(xCoordinate - 0.5);
    }
    /*End of obtained code from Chux*/
    return roundedX;
}
/*
 * Purpose: The submodule below gets the YCoordinate by multiplying the
           distance by sin(radeons). This returns the YCoordinate as an int.
            This is used in the execute functions to get Y2.
 * Import: distance, angle
 * Export: roundedY
 */
int getYCoordinate(double distance, double angle)
{
    int roundedY = 0;
    double yCoordinate, radeons;
    radeons = (angle * PI)/180;
    yCoordinate = (distance) * sin(radeons);
   /*Obtained from chux*/
    /*https://stackoverflow.com/questions/2570934/how-to-round-
      floating-point-numbers-to-the-nearest-integer-in-c */
     /* (Accessed on October 7 2018)*/
    if(yCoordinate > 0)
    {
        roundedY = (int)(yCoordinate + 0.5);
    }
    else
    {
        roundedY = (int)(yCoordinate - 0.5);
    }
    /*End of code obtained from chux*/
    return roundedY;
}

/*
 * Purpose: to keep track of the current angle whenever rotate is called.
 *          Called if string is "rotate", to keep track of current angle. In
 *          addition, tells draw which direction to draw in.
 * Import: value, currentAngle
 * Export: NONE
 */
void executeRotate(char* value, double *currentAngle)
{
    double moveValue;
    moveValue = convertDouble(value); /*convert to double*/   
    *currentAngle += moveValue; /*add to current angle to keep track*/
}

/*
 * Purpose: keeps track of current X and Y Coordinates as well as
 *          writes them to file. This function is used if command 
 *          is "move". 
 * Import: value, *XCoordinate, *YCoordinate, currentAngle, appendFile
 * Export: NONE
 */
void executeMove(char* value, double *XCoordinate, double *YCoordinate, 
                 double currentAngle, FILE* appendFile)
{
    int xValue;
    int yValue;
    double moveValue; 
    fprintf(appendFile, "(%f,%f)-", *XCoordinate, *YCoordinate); 
    /*Append to file*/
    #ifdef DEBUG /*check for debug*/
    fprintf(stderr,"(%f,%f)-",*XCoordinate,*YCoordinate); /*print to terminal*/
    #endif
    moveValue = convertDouble(value); /*convert value to double*/
    xValue = getXCoordinate(moveValue, currentAngle); /*get x2 and y2*/
    yValue = getYCoordinate(moveValue, currentAngle);
     /*get new x and y coordinates*/
    *XCoordinate += xValue;/*change x1 and y1*/
    *YCoordinate -= yValue;
    fprintf(appendFile, "(%f,%f)\n",*XCoordinate, *YCoordinate); /*append*/
    #ifdef DEBUG
    fprintf(stderr, "(%f,%f)\n", *XCoordinate, *YCoordinate);
    #endif
    /*update x and y position*/ 
}

/*
 * Purpose: To keep track of current coordinates as well as draw the line.
 *          This function is called if command is draw. Used to draw the 
 *          graphics.
 * Import: value, *xCoordinate, yCoordinate, pattern, currentAngle,appendFile
 * Export: NONE
 */
void executeDraw(char* value, double* xCoordinate, double* yCoordinate, 
                char pattern, double currentAngle, FILE* appendFile)
{
    PlotFunc myFunc = &plotter; /*initialise plotter function for line*/
    int xValue, yValue, xPrev, yPrev;
    double moveValue;
    moveValue = convertDouble(value)-1; /*convert to double*/
    fprintf(appendFile, "(%f,%f)-", *xCoordinate, *yCoordinate); /*append*/
    #ifdef DEBUG /*check for double*/
    fprintf(stderr, "(%f,%f)-", *xCoordinate, *yCoordinate);
    #endif
    xValue = getXCoordinate(moveValue, currentAngle); /*get x2 and y2*/
    yValue = getYCoordinate(moveValue, currentAngle); 
    /*get new X and Y coordinates*/
    xPrev = (int)*xCoordinate; /*Store x1 and y1 in temp variables for line 
                                function*/
    yPrev = (int)*yCoordinate;
    *xCoordinate += xValue; /*Change x1 and y1 to x2 and y2 sum*/
    *yCoordinate -= yValue;
    line(xPrev, yPrev,(int)*xCoordinate,(int)*yCoordinate, myFunc, &pattern);
    fprintf(appendFile, "(%f,%f)\n",*xCoordinate, *yCoordinate);
    xValue = getXCoordinate(1, currentAngle); /*get x2 and y2*/
    yValue = getYCoordinate(1, currentAngle); 
    *xCoordinate += xValue; /*Change x1 and y1 to x2 and y2 sum*/
    *yCoordinate -= yValue;
    /*Call line function. This draws the line and passes the required values*/
    #ifdef DEBUG /*check debug is defined*/
    fprintf(stderr, "(%f,%f)\n", *xCoordinate, *yCoordinate);
    #endif
}
/*
 * Purpose: To change the foreground colour. Called when command is "fg"
 * Import: *foreground, value
 * Export: NONE
 */
void executeFg(int *foreground, char* value)
{
    #ifndef SIMPLE
    int fgColour;
    *foreground = convertInt(value);   
    fgColour = *foreground;
    /* convert colour value*/
     /*update foreground colour*/
    setFgColour(fgColour);
    /*set foreground colour*/
    #else
    setFgColour(0);
    #endif
}
/*
 * Purpose: To change the background colour. Called when command is "bg"
 * Import: *background, value
 * Export: NONE
 */
void executeBg(int* background, char* value)
{
    #ifndef SIMPLE   
    int bgColour;
    /*Check number of elements on line*/
    *background = convertInt(value);
    /*convert background colour to an integer*/
    bgColour = *background;
    /*update background colour*/
    setBgColour(bgColour);
    /*set background colour*/
    #else 
    setBgColour(7);
    #endif
}  
/*
 * Purpose: Update pattern. Called when pattern is the command. 
 *          Indicates current pattern for plotter function
 * Import: value, pattern
 * Export: NONE
 */
void executePattern(char* value, char* pattern)
{
    *pattern = value[0];
}                       
