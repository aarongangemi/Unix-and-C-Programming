/*Guard to ensure files are not duplicated*/
#ifndef LINKEDLIST_H
/*Guard to ensure files are not duplicated*/
#define LINKEDLIST_H
/*Defines boolean values to check list is empty or not*/
#define boolTrue 1
/*Defines boolean values to check list is empty or not*/
#define boolFalse 0
/* The struct below creates a LinkedList Node for the Linked List
 * It takes the data which is the line read in from file, and contains
 * a next which is used for looping through the list*/
typedef struct LinkedListNode{
    void* data;
    struct LinkedListNode* next;
}LinkedListNode;

/*The struct below is the Linked list struct which creates the list.
 * It contains the head and tail as the list is single linked, double ended.
 * It stores Linked List nodes for iteration*/
typedef struct{
    LinkedListNode* head;
    LinkedListNode* tail;
}LinkedList;
/* the struct below is used to store the command and value.
 * Both the command and value are of size 8 and 5. This is 
 * purposely done as the max command and value is of that size
 * ensuring that there will always be room.*/
typedef struct{
    char newCommand[8];
    char newValue[5];
}newString;

/* To create the linked list*/
LinkedList* createList();


/*
 * Purpose: Insert element at end of list. This is used prodominantly
 * in IO to add the commands to the list. The inserted elements
 * are looped through to check the command.
 */
void insertLast(newString line, LinkedList* list);


 /* Purpose: To free all nodes and data in the linked list. 
  * This function is used so valgrind doesn't have any
  * memory problems with the program and memory leaks
  * do not exist within the program.
  */
void freeLinkedList(LinkedList* list);

/* Purpose: check if list is empty or not. Used in the insert methods.*/
int isEmpty(LinkedList* list);

/*
 * Purpose: To display the list. This function was solely used for the
 * testing of the list.
 */
void printList(LinkedList* list);
#endif
