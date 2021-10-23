#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *getUsersInput()
{
    char *ch1;
    ch1=malloc(sizeof(char));

    printf( "Enter a value :");
    scanf("%s", ch1);

    return ch1;
}

int isDigitOnly(const char *s)
{
    for (int i = 0; i < strlen(s); i++) {
        if(isdigit(s[i]) == 0){
            if(!(s[i] == '.' || s[i] == ',')){
                return 0;
            }
        }
    }

    return 1;
}

int main( ) {
    char *userInput;
    userInput = getUsersInput();

    printf( "\nYou entered: %s \n\n", userInput);

    if(isDigitOnly(userInput)){
        printf( "And it's digit only\n");
    }else{
        printf( "And it's NOT digit only\n");
    }

    return 0;
}
