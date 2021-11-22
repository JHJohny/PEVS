#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    Function doesn't tolerate float or double numbers!
    */
    for (int i = 0; i < strlen(s); i++) {
        if(isdigit(s[i]) == 0){
            return 0;
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

        //Handle if it's digit only input
        if(isDigitOnly(entered_year) && atoi(entered_year) > 0) {
            selected_year=atoi(entered_year);
            break;
        }

        //If one of conditions above were not met - we need to ask user for input again
        printf("---Prepac, rok si zadal nespravne, prosim opakuj.\n\n");
    }

    //Handle proper day entering
    while(1) {
        char* entered_start_day = getUsersInput("Na ktorý deň padne prvý január v tomto roku?");

        //Handle if it's digit only input and in range of week
        if(isDigitOnly(entered_start_day) && atoi(entered_start_day) >= 1 && atoi(entered_start_day) <= 7) {
            selected_starting_day=atoi(entered_start_day);
            break;
        }

        //If one of conditions above were not met - we need to ask user for input again
        printf("---Prepac, den si zadal nespravne, prosim opakuj.\n\n");
    }

    return 0;
}