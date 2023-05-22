#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

// A node in the linked list
struct Node
{
    int data;
    struct Node * next;
};

// The beginning of the linked list
struct Start
{
    int size;
    struct Node * first;
};

// Print the contents of the list
void printList(struct Start * theList);

// Add a new node to the list
void append(int newData, struct Start * theList);

// Clean up the memory used by the list
void cleanUp(struct Start * theList);

// Return a pointer to the end node
struct Node * getLast(struct Start * theList);

#endif // NODE_H_INCLUDED
