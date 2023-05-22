#ifndef READ_MACHINE_H_INCLUDED
#define READ_MACHINE_H_INCLUDED

#include "Adj_List.h"

// Returns the adjacency list of the newly build Turing machine
struct graphNode ** readTuringMachine(char * fileName, int * listLen);

// Gets the next token, sets the new iterator, and returns the length of the token
int getToken(char ** iter, char * buffer);

#endif // READ_MACHINE_H_INCLUDED
