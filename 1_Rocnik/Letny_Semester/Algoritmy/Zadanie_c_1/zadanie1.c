#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Zadanie 1 is sorting algorithm related
//in assignment, there is explicitly said to use structures, but I don't think it's a necessary.
//Logic - instead of allocating memory for the entire file I could read line by line and insert the elements in order with the binary search

typedef struct zasielkaStruct
{
    int prio;
    char* id;
} zasielka;

void getZasielkyFromFile(zasielka *zasielky, char* fileName)
{
    /*NON ABSTRACT method that reads the priority and ID from the file and writes it the to array
    *
    *This method is very specific logic oriented and could not be reused in any other code. This method gets
    *pre-created array of struct as a param1 and filename as a param2
    *Loop trough the file - line by line and split the line by a space. Splitted tokens (values) are used to create
    *a record in the zasielky array.
    */
    FILE* fileHandler;
    char* line;

    fileHandler = fopen(fileName, "r"); //Just opening of the file

    int zasielkyIndex = 0; //With this index, we will write to the zasielky array
    ///Looping trough the file > LINE BY LINE and extracting priority and ID of the zasielka
    while(fgets(line, 13, fileHandler)) {
        char* splitToken = strtok(line, " "); //First split - priority
        zasielky[zasielkyIndex].prio = atoi(splitToken); //atoi - we want to convert string to int
        splitToken = strtok(NULL, " "); //Second split - ID
        zasielky[zasielkyIndex].id = splitToken;

        //printf("Zasielka index %d has priority %d and ID %s\n", zasielkyIndex, zasielky[zasielkyIndex].prio, zasielky[zasielkyIndex].id); - JUST VERBOSE DEBUG

        //zasielkyIndex = zasielkyIndex + 1; Bad
        //zasielkyIndex += 1; Better
        zasielkyIndex++; //Best
    }

    fclose(fileHandler);
}

int main()
{
    zasielka *zasielky = (zasielka*) malloc(sizeof(zasielka) * 100000);

    getZasielkyFromFile(zasielky, "./DataExample.txt");

    return 0;
}
