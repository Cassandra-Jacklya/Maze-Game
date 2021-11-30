#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/* 
Author: Cassandra Jacklya
Purpose: To store the functions of the linked list
Last modified on: 11th October 2021
*/

/*
void printResult(void *data) 
{
    printf("%d %d %d %d %c\n", ((MazeGame *)data)->snakeRow, ((MazeGame *)data)->snakeCol, ((MazeGame *)data)->playerRow, ((MazeGame *)data)->playerCol, ((MazeGame *)data)->player);
}*/

/*creates the linked list*/
LinkedList *createLinkedList()
{
    LinkedList *LL = NULL;
    LL = (LinkedList *)malloc(sizeof(LinkedList));
    LL->head = NULL;
    LL->count = 0;
    return LL;
}

/*inserts the data at the start of the list*/
void insertStart(LinkedList *list, void *entry)
{
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = entry;  
    newNode->next = list->head; /*make the next value of the new entry to point to the first data in the list*/
    list->head = newNode;   /*make the head to point to the new entry*/
    list->count++;  /*increment the count*/
}

/*removes the first element in the list*/
void *removeStart(LinkedList *list)
{
    void *data = NULL;  
    LinkedListNode *start = list->head; /*point to the first element in the list*/
    if (start != NULL)  /*if list is not empty*/
    {
        /*remove the first element in the list*/
        data = start->data; 
        list->head = start->next;
        free(start);    /*free start pointer*/
        list->count--;  /*decrement the count*/
    }
    return data;
}

/*insert the element at the last position in the list*/
void insertLast(LinkedList *list, void *entry)
{
    LinkedListNode *curr = list->head;  /*go to the first element in the list*/
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = entry;
    newNode->next = NULL;
    if (curr == NULL)   /*checks if list is currently empty*/
    {
        /*simply point the head to the new entry*/
        list->head = newNode;
        list->count++;
    }
    else
    {
        while ((curr->next) != NULL)    /*if the current pointer is not pointing to the last node*/
        {
            curr = curr->next;     /*go to the next node*/
        }
        newNode->next = curr->next; /*point the new entry's next to the last node's next*/
        curr->next = newNode;   /*point the previous last node to the new entry*/
        list->count++; /*increment the count*/
    }
}

/*gets the first element in the list*/
void *getTop(LinkedList *list)
{
    void *data = NULL;
    LinkedListNode *start = list->head; /*points to the first node in the list*/
    if (start != NULL)  /*if list is not empty*/
    {
        data = start->data; /*get the top data*/
    }
    return data;
}

/*removes the last element in the list*/
void *removeLast(LinkedList *list)
{
    void *data = NULL;
    LinkedListNode *curr = list->head;  /*points to the first node in the list*/
    LinkedListNode *last = NULL;
    if (curr == NULL)   /*if list is empty*/
    {
        printf("List is empty");    /*optput message*/
    }
    else 
    {
       if (list->count == 1)    /*checks if there is only one node*/
       {
            data = curr->data;  /*gets the data from the only node*/
            list->head = NULL;  /*make the list empty*/
       }
       else
       {
            while (curr->next != NULL)  /* if the current node is not the second last node*/
            {
                last = curr;    
                curr = curr->next;  /*go to the next node*/
            }
            data = curr->data;  /*gets the last node*/
            last->next = curr->next;    /*make the second last node to be the last node*/
       }
        free(curr); /*free pointer*/
        list->count--; /*decrement count*/
    }
    return data;
}

/*prints the linked list*/
void printLinkedList(LinkedList *list, listFunc funcPtr)
{
    LinkedListNode *curr = list->head;  /*point to the first node in the list; NULL if empty*/
    while(curr != NULL) /*if list is not empty*/
    {
        (*funcPtr)(curr->data); /*use function pointer to print current node*/
        curr = curr->next;  /*go to the next node*/
    }
}

/*free existing pointers in the linked list*/
void freeLinkedList(LinkedList *list, listFunc funcPtr)
{
    LinkedListNode *curr = list->head;
    LinkedListNode *nextCurr = NULL;

    while (curr != NULL)    /*if list is not empty*/
    {
        nextCurr = curr->next;  /*let the next pointer point to the next node*/
        (*funcPtr)(curr->data); /*remove the current pointer*/
        free(curr); /*free pointer*/
        curr = nextCurr;    /*go to the next node*/
    }
    free(nextCurr); 
    free(curr);
    free(list); /*free remaining pointers*/
}