#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>   // stat
#include <stdbool.h>    // bool type
#include <regex.h>
#include <ctype.h>

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

char *readFile(char *filepath){
    return "";
}

char *ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

int main( ){
    float lowestNumber=0.0;
    float highestNumber=0.0;
    double numbersSum=0.0;
    double averageNumber=0.0;

    int numbersCount=0;
    int hasBeenLowestNumberFound=0;

    char *filepath;
    filepath = getUsersInput("Prosim zadaj absolutnu cestu k suboru - vratane nazvu suboru (Stlac enter, ak subor sa nachadza tam, kde je skore.c subor): ", "./dataf.txt");

    //Checking if file exists
    if(doesFileExist(filepath)){
        printf("Subor najdeny - OK\n");
    }else{
        printf("Subor neexistuje!\n");
        return 0;
    }

    //File reading part
    char *fileContent = ReadFile(filepath);

    //Number parsing part
    char *p = fileContent;
    while (*p) { // Loop trough characters
        if ( isdigit(*p) || ( (*p=='-'||*p=='+'||*p=='.') && isdigit(*(p+1)) )) {
            //Number found
            double foundNumber = strtof(p, &p); //Read number

            //Handle negative numbers
            if (foundNumber < 0) {
                printf("Zaporne cislo bolo najdene! %.2f\n", foundNumber);
                continue;
            }

            //Handle greater numbers than 100
            if (foundNumber > 100) {
                printf("Pozor bola najdena vyssia hodnota skore ako 100! Hodnota sa bude ignorovat %.2f \n", foundNumber);
                continue;
            }

            //Finding lowest number
            if(hasBeenLowestNumberFound==0) { //It wasn't yet
                lowestNumber=foundNumber;
                hasBeenLowestNumberFound=1;
            }else if(foundNumber < lowestNumber) {
                lowestNumber=foundNumber;
            }

            //Finding highest number
            if(foundNumber > highestNumber) {
                highestNumber = foundNumber;
            }

            //Sum of all numbers - for average calculation
            numbersSum+=foundNumber;

            //Counting of numbers that have been found
            numbersCount++;


        } else {
            //Otherwise, move on to the next character.
            p++;
        }
    }

    if(numbersCount > 0){
        averageNumber = (numbersSum/numbersCount);
        printf("V subore bolo %d skore \n", numbersCount);
        printf("Najmensia hodnota je %.2f \n", lowestNumber);
        printf("Najväčšia hodnota je %.2f \n", highestNumber);
        printf("Priemer všetkých hodnôt v tomto súbore je %.2f \n", averageNumber);
    }else{
        printf("V subore neboli najdene ziadne cisla!\n");
    }

    return 0;
}
