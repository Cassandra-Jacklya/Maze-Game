/* 
Author: Cassandra Jacklya
Purpose: Header file for LinkedList.c
Last modified on: 11th October 2021
*/

#ifndef LIST_GUARD
#define LIST_GUARD
typedef struct LinkedListNode
{
    void *data;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct
{
    LinkedListNode *head;
    int count;
} LinkedList;

typedef struct 
{
    int playerRow;
    int playerCol;
    int snakeRow;
    int snakeCol;
    char player;
} MazeGame;

typedef void (*listFunc)(void *data);
LinkedList* createLinkedList();
void insertStart(LinkedList *list, void *entry);
void *removeStart(LinkedList *list);
void insertLast(LinkedList *list, void *entry);
void *removeLast(LinkedList *list);
void *getTop(LinkedList *list);
void printLinkedList(LinkedList *list, listFunc funcPtr);
void freeLinkedList(LinkedList *list, listFunc funcPtr);
#endif