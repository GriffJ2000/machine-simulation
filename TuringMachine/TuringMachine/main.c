#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Adj_List.h"
#include "read_machine.h"

int main()
{
    int testString[7] = {97, 97, 97, 98, 98, 98};
    char fileName[10] = "test.txt";
    int length = 0;
    struct graphNode ** nodeList = readTuringMachine(fileName, &length);
    int halts = TuringTest(nodeList[0], testString, 6, 20, 100);

    printAdjList(nodeList, 4);

    if (halts == 1)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Not Pass\n");
    }

    return(1);
}
