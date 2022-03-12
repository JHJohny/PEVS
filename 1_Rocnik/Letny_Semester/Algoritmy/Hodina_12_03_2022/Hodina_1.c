#include <stdlib.h>

typedef struct myStruct
{
    int cislo;
    char pismeno;
} myStruct_t;

int main()
{
    myStruct_t *struct1 = NULL;

    struct1 = (myStruct_t*) malloc(sizeof(myStruct_t) * 10);
    int nums[5] = {1, 2, 3, 5, 8};



    return 0;
}