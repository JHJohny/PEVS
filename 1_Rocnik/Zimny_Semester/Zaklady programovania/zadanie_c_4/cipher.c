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

int main() {
    char *crypted_file_name="text.txt";
    char *key_file_name="key.txt";
    char *descrypted_file_name="translation.txt";

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