#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

/*
Append a new item to the list
*/
void append(int newData, struct Start * theList)
{
    // Allocate memory for a new node
    struct Node * toAdd = (struct Node*) malloc(sizeof(struct Node));

    // Check that the memory has been allocated
    if (toAdd == NULL)
    {
        printf("Unable to allocate heap memory.\n");
        return;
    }

    // Assign the member variables
    toAdd->data = newData;
    toAdd->next = NULL;

    // Check if the list is empty
    if (theList->size < 1)
    {
        theList->first = toAdd;
        theList->size++;
        return;
    }

    struct Node * last = getLast(theList);
    last->next = toAdd;

    // Increment the list size
    theList->size++;

    return;

}

/*
    Returns the node at the end of the list
*/
struct Node * getLast(struct Start * theList)
{
    if (theList->size < 1)
    {
        printf("This list is empty.");
        return(0);
    }

    struct Node * current = theList->first;

    for (int i = 0; i < theList->size - 1; i++)
    {
        current = current->next;
    }

    return current;
}

/*
Free up the memory associated with the list.
Note: This does not free the start node if it is
dynamically allocated. That has to be done elsewhere.
*/
void cleanUp(struct Start * theList)
{
    if (theList->size == 0)
    {
        free(theList);
        return;
    }
    else if (theList->size == 1)
    {
        free(theList->first);
        return;
    }

    struct Node * ptr1 = theList->first;
    struct Node * ptr2 = theList->first->next;

    for (int i = 0; i < theList->size - 1; i++)
    {
        free(ptr1);
        ptr1 = ptr2;
        ptr2 = ptr2->next;
    }

    free(ptr1);
    free(ptr2);
}

/*
Print the elements of a list
*/
void printList(struct Start * theList)
{
    if (theList->size < 1)
    {
        return;
    }

    struct Node * curr = theList->first;

    for (int i = 0; i < theList->size; i++)
    {
        printf("%d\n", curr->data);
        curr = curr->next;
    }

}
