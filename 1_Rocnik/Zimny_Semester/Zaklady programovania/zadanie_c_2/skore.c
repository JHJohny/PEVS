#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>   // stat
#include <stdbool.h>    // bool type

bool doesFileExist(char *filepath){
    struct stat   buffer;
    return (stat (filepath, &buffer) == 0);
}

char *getUsersInput(char *askingSentence, char *defaultString){ //Ask user for his input
    char *usersInput;
    usersInput=malloc(sizeof(char));

    printf("%s", askingSentence);
    scanf("%99[^\n]", usersInput);

    if(strlen(usersInput) == 0){ //For checking if user entered just nothing
        return defaultString;
    }

    return usersInput;
}

int main( ){
    char *userInput;
    userInput = getUsersInput("Prosim zadaj absolutnu cestu k suboru (Stlac enter, ak subor sa nachadza tam, kde je skore.c subor): ", "./dataf_1.txt");

    if(doesFileExist(userInput)){
        printf("Yay it works!\n");
    }else{
        printf("It doesn't work!\n");
    }

    return 0;
}
