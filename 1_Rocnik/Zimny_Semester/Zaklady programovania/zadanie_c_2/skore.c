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

char *readFile(char *filepath){
    return "";
}

char* ReadFile(char *filename)
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
    char *filepath;
    filepath = getUsersInput("Prosim zadaj absolutnu cestu k suboru - vratane nazvu suboru (Stlac enter, ak subor sa nachadza tam, kde je skore.c subor): ", "./dataf_1.txt");

    //Checking if file exists
    if(doesFileExist(filepath)){
        printf("Subor najdeny - OK\n");
    }else{
        printf("Subor neexistuje!\n");
        return 0;
    }

    char *fileContent = ReadFile(filepath);
    printf("File content %s\n", fileContent);

    return 0;
}
