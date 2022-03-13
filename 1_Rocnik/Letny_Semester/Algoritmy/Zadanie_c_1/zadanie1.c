#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Zadanie 1 is sorting algorithm related
//in assignment, there is explicitly said to use structures, but I don't think it's a necessary.
//Logic - instead of allocating memory for the entire file I could read line by line and insert the elements in order with the binary search

void test(char* fileName)
{
    FILE* fileHandler;
    char line[12];

    fileHandler = fopen(fileName, "r");

    while(fgets(line, 12, fileHandler)) {
        char* prio = strtok(line, " ");
        printf("%s", prio);
    }

    fclose(fileHandler);
}

int main()
{
    /*
    typedef struct zasielkaStruct
    {
        int prio;
        char* id;
    } zasielka;

    zasielka *zasielky = (zasielka*) malloc(sizeof(zasielka) * 100000);

    for(int x = 0; x < 10; x++)
    {
        zasielky[x].prio = 10 + x;
        zasielky[x].id = "XXX";
    }
    */

    test("./DataExample.txt");

    return 0;
}
