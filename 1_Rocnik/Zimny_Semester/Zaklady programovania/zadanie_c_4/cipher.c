#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>   // stat
#include <stdbool.h>    // bool type

char *ReadFile(char *filename)
{
/*
This function reads the the file and return it as a string.

This function reads the given file (full path) and return it as a string.
Reading consist of dynamic buffer that shouldn't allocate more memory than it's necessary to.
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
/*
This function finds any kind of letter (isalpha) within the string.

This function finds numbers that follow any kind of letter.
*/

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
/*
This function is SPECIFIC CUSTOM function that tries to decipher the message in the given file.

This function takes as a argument three files.
First one contains numbers and letters that are associated to the specific numbers
Second one contains just the numbers, that represent some kind of message that is suppose to be decrypted
Third one is basically just a "placeholder" file where the decrypted message should be stored to
*/
    //Final text array
    char *decrypted_message;
    decrypted_message = malloc(sizeof(char));
    int decrypted_message_index = 0; //Kind of "looping" trough string

    //Firstly we will read number by number from the crypted file name
    FILE* f_crypted_file = fopen(crypted_file_name, "r"); //Read the text - where the message is crypted
    int number = 0;

    char *key_file_content = ReadFile(keys_file_name);

    //Looping trough the numbers that hide the message
    while( fscanf(f_crypted_file, "%d,", &number) > 0 )
    {
        //Decrypt the number that hide the letter
        char decrypted_letter = findLetterAfterInt(key_file_content, number);

        //Check whether a letter was found
        if(decrypted_letter == '\0') {
            printf("Nebolo najdene pismeno ku tomuto cislu! - %d\nProgram sa zastavi, prosim uprav data a spusti program znova.\n", number);
            exit(0);
        }

        decrypted_message[decrypted_message_index] = decrypted_letter;

        //We are dynamically storing decrypted letter one by one to the array
        decrypted_message_index++;
    }

    fclose(f_crypted_file);

    //Message decryption / reading is done - lets save it to the file
    decrypted_message[strlen(decrypted_message)] = '\0'; //Close the array - otherwise any part of memory could be readen
    FILE* f_decrypted = fopen(decrypted_file_name, "w");
    fprintf(f_decrypted, "%s", decrypted_message);
    fclose(f_decrypted);

    printf("Subor - %s sa uspesne desifroval do suboru %s, desifrovana sprava je %s\n\n", crypted_file_name, decrypted_file_name, decrypted_message);
}

bool doesFileExist(char *filepath){
    struct stat   buffer;
    return (stat (filepath, &buffer) == 0);
}

void handleIfTheFileDoesntExist(char *file_name) {
    /*
    This function checks whether file exist or not.

    Function takes one parameter - file name (full path is recommended) and checks where file exist or not.
    If the file doesn't exist - program is stopped
    */

    if(!doesFileExist(file_name)) {
        printf("Tento subor nebol najdeny! - %s \nProsim presun tento subor do zlozky, kde sa nachadza tento .c kod\npotom spusti program znovu.\n\n", file_name);
        exit(0);
    }
}

int main() {
    char *crypted_file_name="./text.txt";
    char *key_file_name="./key.txt";
    char *descrypted_file_name="./translation.txt";

    handleIfTheFileDoesntExist(crypted_file_name);
    handleIfTheFileDoesntExist(key_file_name);
    handleIfTheFileDoesntExist(descrypted_file_name);

    decipherTheText(key_file_name, crypted_file_name, descrypted_file_name);

    return 0;

}