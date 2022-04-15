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

int customBinarySearch(int arr[], int length, int num)
{
    // Doesn't return value of index of the searched element, but iteration

    int l = 0;
    int r = length -1;
    int comparisions = 0;

    while(l <= r)
    {
        comparisions++;
        int mid = l + (r - l) / 2;

        comparisions++;
        if(arr[mid] == num)
        {
            return comparisions;
        }

        comparisions++;
        if(arr[mid] < num)
        {
            l = mid + 1;
        }

        comparisions++;
        if(arr[mid] > num)
        {
            r = mid - 1;
        }
    }
}

int main() {
    int lengthOfArray = 10000; // Array of numbers that will be used for search
    int arrayWithNums[lengthOfArray]; // Actual array of these numbers
    int howManyTimeAlgorithmsShouldBeTested = 2000;
    int resultsFromBruteForceSearch = 0; // Temporary variable used for storing results
    int resultsFromBinarySearch = 0; // Temporary variable used for storing results

    // Creating the array
    for (int i = 0; i < lengthOfArray; i++)
    {
        arrayWithNums[i] = i;
    }

    // Actual testing of the algorithms
    for (int i = 0; i < howManyTimeAlgorithmsShouldBeTested; i++)
    {
        int randomNumber = rand() % lengthOfArray;

        resultsFromBinarySearch += customBinarySearch(arrayWithNums, lengthOfArray, randomNumber);
        resultsFromBruteForceSearch += customBruteForceSearch(arrayWithNums, lengthOfArray, randomNumber);
    }

    // Doing the final calculation + print
    printf("Average bruteforce comparisons - %d\n", resultsFromBruteForceSearch / howManyTimeAlgorithmsShouldBeTested);
    printf("Average binary comparisons - %d\n", resultsFromBinarySearch / howManyTimeAlgorithmsShouldBeTested);

    return 0;
}
