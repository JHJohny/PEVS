#include <stdio.h>

void readNumbersFromfile(char *file_name_with_path, int max_number) {
    FILE* f = fopen(file_name_with_path, "r");
    int number = 0;

    while( fscanf(f, "%d,", &number) > 0 )
    {
        if(number > max_number) {
            printf("Number greater than %d was found! This number will be excluded from the program! - %d", max_number, number);
        }else {
            printf("This is the number %d\n", number);
        }
    }

    fclose(f);
}

int main() {
    char *crypted_file_name="text.txt";
    char *key_file_name="key.txt";
    char *descrypted_file_name="translation.txt";

    readNumbersFromfile(crypted_file_name);

    return 0;
}