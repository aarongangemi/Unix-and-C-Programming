#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
/*
 * Algoritm based on Robert Lafore, "Data Structures and Algorithms in Java"
 * (2002), Pages 199-200
 * **********************************************************************
 * Purpose: Contains methods for creation and modification of linked list
 * Author: Aaron Gangemi
 * Date Modified: 12 October 2018
 */

/*
 * Purpose: To create the linked list
 * Import: NONE
 * EXPORT: Linked list
 */
LinkedList* createList()
{
    LinkedList* list; 
    list = (LinkedList*)malloc(sizeof(LinkedList)); /*Malloc the list*/
    list->head = NULL; /*Set head and tail to NULL*/
    list->tail = NULL;
    return list;
}
/*
 * Purpose: Insert element at end of list. This is used prodominantly
 *          in IO to add the commands to the list. The inserted elements
 *          are looped through to check the command.
 * Import: line, list
 * Export: NONE
 */
void insertLast(newString line, LinkedList* list)
{
    newString* newLine;
    LinkedListNode* newNode;
    newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newLine = (newString*)malloc(sizeof(newString));
    /*Malloc memory for node and data*/
    *newLine = line;
    /*set data*/
    newNode->data = newLine;
    /*add line read in from file to list node created*/
    newNode->next = NULL;
    /*set new node next to null, cause end of list*/
    if(isEmpty(list) == boolTrue) /*check if list is empty*/
    {
        list->head = newNode;
        list->tail = newNode;
        /*set head and tail to new node*/
    }
    else /*if not empty*/
    {   
        list->tail->next = newNode;
        list->tail = newNode;
        /*set tail next to newNode*/
        /*set tail to node*/
    }
    
}
/* 
 * Based on Curtin University COMP1001 Lecture Slides
 * Purpose: To free all nodes and data in the linked list. 
 *          This function is used so valgrind doesn't have any
 *          memory problems with the program and memory leaks
 *          do not exist within the program.
 * Import: list
 * Export: NONE
 */
void freeLinkedList(LinkedList* list)
{
    LinkedListNode* node;
    LinkedListNode* nextNode;
    node = list->head;
    while(node != NULL) /*while list is not empty*/
    {
        nextNode = (*node).next; /* go to next node*/ 
        free(node->data); /*free data in list*/
        free(node); /*free node*/
        node = nextNode; /*current = next*/
    }
    free(list); /*free entire list once*/
}

/*
 * Purpose: check if list is empty or not. Used in the insert methods.
 * Import: list
 * Export: booleanVal (INDICATOR FOR TRUE OR FALSE)
 */
int isEmpty(LinkedList* list)
{
    int booleanVal;
    if(list->head == NULL) /*if list head is NULL*/
    {
        booleanVal = boolTrue; /*list is empty*/
    }
    else
    {
        booleanVal = boolFalse; /*list not empty*/
    }
    return booleanVal;
}

/*
 * Purpose: To display the list. This function was solely used for the
 *          testing of the list.
 * Import: list
 * Export: NONE
 */
void printList(LinkedList* list)
{
    LinkedListNode* currentNode = list->head;
    while(currentNode != NULL) /*while next element exists*/
    {
        printf("%s ", ((newString*) currentNode->data)->newCommand);
        printf("%s\n", ((newString*) currentNode->data)->newValue);
        currentNode = currentNode->next;
        /*print and go to next node*/
    }
}
