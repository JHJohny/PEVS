#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Zadanie 1 is sorting algorithm related
//in assignment, there is explicitly said to use structures, but I don't think it's a necessary.

typedef struct zasielkaStruct
{
    int prio;
    char* id;
} zasielka;

void getZasielkyFromFile(zasielka *zasielky, char* fileName)
{
    /*NON ABSTRACT method that reads the priority and ID from the file and writes it the to array
    *
    *Params:
    *@zasielky - *zasielka: list of custom structure
    *@fileName - *char: name of the file - full path
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


void countingSort(int a[], int n, int place) // function to implement counting sort
{
    /*Sort array in order based on the @place parameter
    *
    *Params:
    *@a - int[]:    array that is suppose to be sorted
    *@n - int:      length of the array > could be null
    *@place - int:   place that we are sorting, it increase by 10s
    *
    *Counting sort reads nth place of each digit in array and note occurence of that digit into a array
    *Then calculate cumulative sum of that array - n element in array is equal to that element plus element before
    *Then based on occurences that were noted in the step 1, algorithm know where the specific number is suppose to be placed to
    *In the last step, inputed array is being overwritten by a temporary one - where the sortion happened.
    */

    int output[n + 1];
    int occurences[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //This array represent occurence of each digit from the nth place

    //Looping trough the list and recording the count of digit from the nth place
    for (int i = 0; i < n; i++)
    {
        int moduleFromElement = ((a[i] / place) % 10); //This modulo represents digit from 0-10 from the nth place we are sorting

        occurences[moduleFromElement]++; //Increment on nth place, means we have one more digit ending with this number - number > moduleFromElement
    }

    //Summing out the values with the predecessor values - cumulative sum
    for (int i = 1; i < 10; i++)
    {
        occurences[i] += occurences[i - 1];
    }

    //Sort numbers in order, based on the nth place
    for (int i = (n - 1); i >= 0; i--)
    {
        int inputValue = (a[i] / place);
        int indexFromOccurences = occurences[inputValue % 10];

        output[(indexFromOccurences) - 1] = a[i]; //Cannot use -- because decrement would be applied to variable before, not for output index itself
        occurences[inputValue % 10]--; //% 10 - because we are working only with the nth integer, and we want it decrement, because we already "wrote down" value from this occurence
    }

    //Just update the array, with the sorted one (Sorted one, is only within the nth place!)
    for (int i = 0; i < n; i++)
    {
        a[i] = output[i];
    }
}

// function to implement radix sort
void radixsortCustom(int a[], int n) {

    int place = 1;
    for(int i = 1; i < 5; i++) //We are sorting up to 9999 priority > 1st, 10nth, 100nth, 1000nth places
    {
        countingSort(a, n, place);
        place *= 10;
    }
}

int main()
{
    /*
    zasielka *zasielky = (zasielka*) malloc(sizeof(zasielka) * 100000); //Creating list of zasielky

    getZasielkyFromFile(zasielky, "./DataExample.txt");
    */

    int fictionalZasielky[] = {1, 90, 11, 20, 43, 29, 88, 77, 54, 48, 85, 92, 9999, 9922, 9123};
    int lengthOfZasielky = sizeof fictionalZasielky / sizeof fictionalZasielky[0];

    radixsortCustom(fictionalZasielky, lengthOfZasielky);

    return 0;
}
