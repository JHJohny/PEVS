#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void readNumbersFromfile(char *file_name_with_path) {
    FILE* f = fopen(file_name_with_path, "r");
    int number = 0;

    while( fscanf(f, "%d,", &number) > 0 )
    {
        printf("This is the number %d\n", number);
    }

    fclose(f);
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

char findLetterAfterInt(char *my_string, int num) {
    char *num_as_string = malloc(sizeof(char));
    sprintf(num_as_string, "%d", num);
    int new_number = 1; //Remember if we are looping trough the new number

    for(int i = 0; i < strlen(my_string); i++) {

        //If it equals - we may start investigating if it's the number, that we are looking for
        if((my_string[i] == num_as_string[0]) && new_number == 1) {
            int is_number_found = 1;

            for(int j = 0; j < strlen(num_as_string); j++) {
                if(num_as_string[j] != my_string[i+j]) {
                    is_number_found = 0; //It's not the correct number
                }
            }

            //Finally continuing after the found number to find a letter
            if(is_number_found == 1) {
                for(int k = i+strlen(num_as_string); k < strlen(my_string); k++) {
                    if(isalpha(my_string[k])) {
                        return my_string[k];
                    }
                }
            }
        }

        //We want to reset the sequence of the numbers - otherwise letter assigned to 19, could be found as a letter asigned to 9
        if(!isdigit(my_string[i])) {
            new_number = 1;
        }else {
            new_number = 0;
        }
    }

    return (char) 0; //If nothing was found - return nothing
}

void decipherTheText(char *keys_file_name, char *crypted_file_name, char *decrypted_file_name) {
    //TODO append to the array

    //Firstly we will read number by number from the crypted file name
    FILE* f_crypted_file = fopen(crypted_file_name, "r"); //Read the text - where the message is crypted
    int number = 0;

    char *key_file_content = ReadFile(keys_file_name);

    while( fscanf(f_crypted_file, "%d,", &number) > 0 )
    {
        char decrypted_letter = findLetterAfterInt(key_file_content, number);

        printf("%c", decrypted_letter);
    }

    fclose(f_crypted_file);

    printf("\n\n"); //Just a aesthetic
}

int main() {
    char *crypted_file_name="text.txt";
    char *key_file_name="key.txt";
    char *descrypted_file_name="translation.txt";

    decipherTheText(key_file_name, crypted_file_name, descrypted_file_name);

    return 0;

    char tmp_text[] = "This is my test temporary string 12 g svdvf";

    char letter = findLetterAfterInt(tmp_text, 12);

    if(letter != '\0' && letter != 0) {
        printf("This is the found letter %c \n", letter);
    }else {
        printf("The letter was not found\n");
    }

    return 0;

    readNumbersFromfile(crypted_file_name);

    return 0;
}