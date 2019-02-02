/*Guard to ensure files are not duplicated*/
#ifndef TURTLEGRAPHICS_H
/*Guard to ensure files are not duplicated*/
#define TURTLEGRAPHICS_H
#include "LinkedList.h"
/*Defines the value of pi to 5.d.p. This is used to calculate the radians for 
 * X2 and Y2
 */
#define PI 3.14159

/*
 * Purpose: to keep track of the current angle whenever rotate is called.
 * Called if string is "rotate", to keep track of current angle. In
 *  addition, tells draw which direction to draw in.
 */
void executeRotate(char* value, double* currentAngle);


/*
 * Purpose: keeps track of current X and Y Coordinates as well as
 * writes them to file. This function is used if command 
 * is "move". 
 */
void executeMove(char* value, double *XCoordinate, double *YCoordinate, double currentAngle, FILE* appendFile);


/* To keep track of current coordinates as well as draw the line.
 * This function is called if command is draw. Used to draw the 
 * graphics.
 */

void executeDraw(char* value, double *xCoordinate, double *YCoordinate, char pattern, double currentAngle, FILE* appendFile);


/* Purpose: To change the foreground colour. Called when command is "fg"*/
void executeFg(int *foreground, char* value);


/* Purpose: To change the background colour. Called when command is "bg"*/
void executeBg(int* background, char* value);



/*
 * Purpose: Update pattern. Called when pattern is the command. 
 * Indicates current pattern for plotter function
 */
void executePattern(char* value, char* pattern);


/* The submodule below get the XCoordinate by multiplying the
 * distance by cos(radeons). Returns the XCoordinate as integer.
 * This is used in the execute commands to get X2
 */
int getXCoordinate(double distance, double angle);


/* The submodule below gets the YCoordinate by multiplying the
 * distance by sin(radeons). This returns the YCoordinate as an int.
 * This is used in the execute functions to get Y2.
 */
int getYCoordinate(double distance, double angle);
#endif
