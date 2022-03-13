#include <stdlib.h>
#include <stdio.h>

//Zadanie 1 is sorting algorithm related
//in assignment, there is explicitly said to use structures, but I don't think it's a necessary.
//Logic - instead of allocating memory for the entire file I could read line by line and insert the elements in order with the binary search

char *ReadFile(char *filename)
{
    /*This function read the whole file
    *
    *This function read the file and return it's content. File could be any size.
    */

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

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

void test(FILE* handler)
{
    /*
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen("./DataExample.txt", "r");
    */

    char line[12];
    while(fgets(line, 12, handler)) {
        printf("%s", line);
    }

    fclose(handler);
}

int main()
{
    /*
    char *fileContent = ReadFile("./DataExample.txt");
    printf("File content is \n%s\n", fileContent);
    */

    FILE* handler = fopen("./DataExample.txt", "r");

    test(handler);

    return 0;
}
