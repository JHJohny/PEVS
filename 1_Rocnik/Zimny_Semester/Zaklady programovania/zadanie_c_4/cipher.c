#include <stdio.h>

void readNumbersFromfile(char *file_name_with_pathx) {
    FILE* f = fopen(file_name_with_path, "r");
    int number = 0;

    while( fscanf(f, "%d,", &number) > 0 )
    {
        printf("This is the number %d\n", number);
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