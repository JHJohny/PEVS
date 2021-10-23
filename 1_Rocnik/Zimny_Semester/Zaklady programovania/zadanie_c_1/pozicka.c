#include <stdio.h>
#include <stdlib.h>

char *substring()
{
    char *ch1;
    ch1=malloc(sizeof(char));

    printf( "Enter a value :");
    scanf("%s", ch1);

    return ch1;
}

int main( ) {

   char str[100];
   char *str_two;

   //printf( "Enter a value :");
   //scanf("%s", str);

    str_two = substring();

   printf( "\nYou entered: %s ", str_two);

   return 0;
}
