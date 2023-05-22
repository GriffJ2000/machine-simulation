#include <stdio.h>
#include <stdlib.h>
#include "read_machine.h"
#include "Adj_List.h"

/*
Gets the next token
*/
int getToken(char ** iter, char * buffer)
{
    // Check if we are on the null termination character
    if (**iter == '\0')
    {
        return 0;
    }

    // Parse the string into the buffer
    for (int i = 0;; i++)
    {
        if (**iter == '\0')
        {
            buffer[i] = '\0';
            return i + 1;
        }

        if (**iter == ' ')
        {
            buffer[i] = '\0';
            *iter = *iter + 1;
            return i + 1;
        }

        // Increment the iterator
        buffer[i] = **iter;

        *iter = *iter + 1;
    }

}

/*
Read a file into a Turing machine
*/
struct graphNode ** readTuringMachine(char * fileName, int * listLen)
{
    // Set up the file handle to read
    FILE * fileHandle = fopen(fileName, "r");

    // Check that the fileHandle pointer is not null
    if (fileHandle == NULL)
    {
        return NULL;
    }

    char buffer[20];

    // Get the first string
    fgets(buffer, 6, fileHandle);

    // Get the number of states
    int numStates = atoi(buffer);

    // Create the states
    struct graphNode ** statesList = malloc(sizeof(struct graphNode*) * (numStates + 1));

    // Build the list of nodes
    for (int i = 0; i < numStates; i++)
    {
        statesList[i] = (struct graphNode*) malloc(sizeof(struct graphNode));
        statesList[i]->vertex = i;
        statesList[i]->numEdges = 0;
        statesList[i]->isAccept = 0;

        *listLen = *listLen + 1;
    }

    statesList[numStates - 1]->isAccept = 1;

    // Declare some variables for the edges
    struct graphNode * from;
    struct graphNode * to;
    int toRead;
    int toWrite;
    int direction;
    char * iter;
    char dir;
    char tokenBuffer[20];

    // Add edges to the nodes
    while (fgets(buffer, 20, fileHandle))
    {
        iter = &buffer[0];
        // Get the from node
        getToken(&iter, tokenBuffer);
        from = statesList[atoi(tokenBuffer)];

        // Get the read node
        getToken(&iter, tokenBuffer);
        toRead = (int) tokenBuffer[0];
        toWrite = (int) tokenBuffer[1];
        dir = tokenBuffer[2];

        switch (dir)
        {
            case 'R':
                direction = 1;
                break;
            case 'L':
                direction = -1;
                break;
            case 'S':
                direction = 0;
                break;
        }

        // Get the to node
        getToken(&iter, tokenBuffer);
        to = statesList[atoi(tokenBuffer)];

        addEdge(from, to, 0, toRead, toWrite, direction);

    }

    fclose(fileHandle);
    return statesList;
}
