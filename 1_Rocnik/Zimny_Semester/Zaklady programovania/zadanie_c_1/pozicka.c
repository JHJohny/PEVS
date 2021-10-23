#include <stdio.h>
#include <stdlib.h>

char *getUsersInput()
{
    char *ch1;
    ch1=malloc(sizeof(char));

    printf( "Enter a value :");
    scanf("%s", ch1);

    return ch1;
}

int main( ) {
    char *userInput;
    userInput = getUsersInput();

    printf( "\nYou entered: %s \n", userInput);

    return 0;
}
