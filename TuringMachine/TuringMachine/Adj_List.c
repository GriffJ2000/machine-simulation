#include "Adj_List.h"
#include <stdlib.h>
#include <stdio.h>

/*
Add an edge to a node
*/
void addEdge(struct graphNode * from, struct graphNode * to, int weight, int toRead, int toWrite, int dir)
{
    // Set up the new edge
    struct edge * toAdd = (struct edge*) malloc(sizeof(struct edge));
    toAdd->weight = weight;
    toAdd->read = toRead;
    toAdd->write = toWrite;
    toAdd->headMove = dir;
    toAdd->next = to;

    // Set up the new pointer array for from
    struct edge** newArr = malloc(sizeof(struct edge*) * (from->numEdges + 1));

    // Check that the array isn't empty already
    if (from->numEdges == 0)
    {
        newArr[0] = toAdd;
        from->edges = newArr;
        from->numEdges = 1;

        return;
    }

    // Put the edges into the new array
    for (int i = 0; i < from->numEdges; i++)
    {
        newArr[i] = from->edges[i];
    }

    // Put the new edge in the array
    newArr[from->numEdges] = toAdd;

    // Point edges to the new array
    from->edges = newArr;

    // Update the size
    from->numEdges = from->numEdges + 1;
}

/*
Clean up the memory associated with edges
*/
void cleanEdges(struct graphNode * toClean)
{
    for (int i = 0; i < toClean->numEdges; i++)
    {
        free(toClean->edges[i]);
    }

    free(toClean->edges);
    toClean->numEdges = 0;
}

/*
Cycle the FA and return the new current node
*/
struct graphNode * FACycle(struct graphNode * currState, int nextChar)
{
    for (int i = 0; i < currState->numEdges; i++)
    {
        if (currState->edges[i]->weight == nextChar)
        {
            return currState->edges[i]->next;
        }
    }

    return NULL;
}

/*
Returns true if the toTest is rejected
*/
int FATest(struct graphNode * start, int toTest[], int size)
{
    struct graphNode * currState = start;

    for (int i = 0; i < size; i++)
    {
        currState = FACycle(currState, toTest[i]);
        if (currState == NULL)
        {
            return 0;
        }

    }

    // Check that we end on state 0 which is the accept state
    if (currState != NULL && currState->isAccept == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
Return true if the turing machine halts on the string
Note: The rules for this implementation do not allow the
head to move off the left edge of the tape
*/
int TuringTest(struct graphNode * start, int toTest[], int size, int tapeLen, int maxCycles)
{
    // Get the tape set up
    int * tape = malloc(sizeof(int) * (tapeLen + 2));

    // The first int is two which corresponds to ascii character STX (start of text)
    // This is the end of the tape
    tape[0] = 2;

    // Read the string into the tape
    for (int i = 0; i < size; i++)
    {
        tape[i + 1] = toTest[i];
    }

    // Fill the rest of the tape with 78 (N for NULL)
    for (int i = size + 1; i < tapeLen + 2; i++)
    {
        tape[i] = 78;
    }

    // Let the final character be 3 (end character in ascii)
    tape[tapeLen + 1] = 3;

    // Place the tape index on the first character
    int tapeIndex = 1;

    // Set up the state pointer
    struct graphNode * curr = start;

    // Run the test on the given turing machine
    for (int i = 0; i < maxCycles; i++)
    {
        // Reject if we go off the left edge
        if (tape[tapeIndex] == 2)
        {
            return 0;
        }

        // Reject if we go off the right edge
        if (tape[tapeIndex] == 3)
        {
            return 0;
        }

        // Accept if the state is an accept state
        if (curr->isAccept == 1)
        {
            return 1;
        }

        int found = 0;

        // Check throught the current nodes's adjacency list
        for (int j = 0; j < curr->numEdges; j++)
        {
            if (curr->edges[j]->read == tape[tapeIndex])
            {
                // Update the tape index and the current state
                tape[tapeIndex] = curr->edges[j]->write;
                tapeIndex = tapeIndex + curr->edges[j]->headMove;
                curr = curr->edges[j]->next;
                found = 1;
                break;
            }
        }

        // Check that a matching edge was found
        if (found == 0)
        {
            return 0;
        }

    }

    free(tape);

    return 0;

}

/*
Print the given adjacency list
*/
void printAdjList(struct graphNode ** nodeList, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d: ", nodeList[i]->vertex);

        for (int j = 0; j < nodeList[i]->numEdges; j++)
        {
            printf("%d -> ", nodeList[i]->edges[j]->next->vertex);
        }
        printf("\n");
    }
}
