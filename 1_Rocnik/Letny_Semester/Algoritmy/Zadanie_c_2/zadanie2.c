#include <stdio.h>
#include <stdlib.h>

int customBruteForceSearch(int arr[], int length, int num) // I could dynamically get length of array - but that wouldn't be sufficient
{
    // Doesn't return value of index of the searched element, but number of comparisions 

    int nthIterationIndex = 0; // Temporary index for storing how many times did we do comparison
    for(int i = 0; i < length; i++)
    {
        if (arr[i] == num)
        {
            break;
        }

        nthIterationIndex++;
    }

    return nthIterationIndex; // Technically we could just return i, but
}

int customBinarySearch()
{
    // Doesn't return value of index of the searched element, but iteration

    return 0;
}

int main() {

    int lengthOfArray = 10000;
    int howManyTimeAlgorithmsShouldBeTested = 1000;

    int arrayWithNums[lengthOfArray];

    for (int i = 0; i < lengthOfArray; i++)
    {
        arrayWithNums[i] = i;
    }

    int randomNumber = rand() % (lengthOfArray + 1 - 0) + 0;
    printf("Random number is %d\n", randomNumber);

    
    return 0;
}
