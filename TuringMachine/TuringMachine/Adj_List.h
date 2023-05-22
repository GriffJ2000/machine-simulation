#ifndef ADJ_LIST_H_INCLUDED
#define ADJ_LIST_H_INCLUDED
#define LEFT -1
#define RIGHT 1
#define STAY 0

/*
Each graph node has a vertex and a list of edges to other vertices
*/
struct graphNode
{
    // The vertex label
    int vertex;

    // The number of edges from this node
    int numEdges;

    // Is this an accept state?
    int isAccept;

    // The list of edges from this node
    struct edge** edges;
};

/*
Each edge has a weight, head move direction, read, write, and pointer to next node
*/
struct edge
{
    // The weight of the edge
    int weight;

    // Read
    int read;

    // Write
    int write;

    // Head move direction
    int headMove;

    // The next node
    struct graphNode * next;
};

// Add an edge from one node to another node
void addEdge(struct graphNode * from, struct graphNode * to, int weight, int toWrite, int toRead, int dir);

// Clean up the edge list of a vertex
void cleanEdges(struct graphNode * toClean);

// FA cycle
struct graphNode * FACycle(struct graphNode * currState, int next);

// Test a string with an FA
int FATest(struct graphNode * start, int toTest[], int size);

// Test a string with a Turing machine
int TuringTest(struct graphNode * start, int toTest[], int size, int tapeLen, int maxCycles);

// Print out the adjacency list
void printAdjList(struct graphNode ** nodeList, int len);

#endif // ADJ_LIST_H_INCLUDED
