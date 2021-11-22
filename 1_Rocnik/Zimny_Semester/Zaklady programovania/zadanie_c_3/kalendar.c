#include <stdio.h>
#include <stdlib.h>

char *getUsersInput(char* askingSentence)
{
    /*
    This function ask user for an input

    Function uses a string parameter and allocate memory for it by calling a function malloc.
    For reading user input uses a scanf function.
    */
    char *ch1;
    ch1=malloc(sizeof(char));

    printf("%s\n", askingSentence);
    scanf("%s", ch1);

    return ch1;
}

int isDigitOnly(const char *s)
{
    /*
    This function check if input parameter is digit only.

    This function if the string that is parsed to the function, contains only a numbers.
    Docstring tolerate a decimal points as a "." OR ",".
    */
    for (int i = 0; i < strlen(s); i++) {
        if(isdigit(s[i]) == 0){
            if(!(s[i] == '.' || s[i] == ',')){
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    int selected_year;
    int selected_starting_day;

    //Handle proper year entering
    while(1) {
        char* entered_year = getUsersInput("Zadaj rok, pre ktorý chceš kalendár?");

        if(isDigitOnly(entered_year)) {
            selected_year=atoi(entered_year);
            break;
        }else {
            printf("Prepac, rok si zadal nespravne, prosim opakuj.");
            continue;
        }
    }

    //Handle proper day entering
    while(1) {
        char* entered_start_day = getUsersInput("Na ktorý deň padne prvý január v tomto roku?");

        if(isDigitOnly(entered_start_day)) {
            selected_starting_day=atoi(entered_start_day);
        }else {
            printf("Prepac, den si zadal nespravne, prosim opakuj.");
            continue;
        }
    }

    if(!isDigitOnly(entered_year) || !isDigitOnly(entered_start_day)) {
        printf
    }

    printf("%s\n", entered_year);

    return 0;
}