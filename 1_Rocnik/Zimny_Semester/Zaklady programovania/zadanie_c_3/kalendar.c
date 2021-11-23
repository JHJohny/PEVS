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

void print_month(char *month, int* week_day_index, int months_days) {
    /*
    This function print the whole month.

    This function print the whole month, based on where the week should start (day index) - Mon, Thue...
    Function use a week index pointer - so the next iteration of this function (next month) could start where the
    previous one finished.
    */
    printf("\n\n");
    printf("          %s        \n", month);
    printf(" P   U   S   Š   P   S   N \n");
    printf("---------------------------\n");

    int j=1; //Just a holder of the current routing day in a WEEK
    int k=1; //Just a hodler of the current routing day in a MONTH
    for(int i=1; i<=months_days; i++) {
        if(j==*week_day_index) {

            //Handle single/double digits days
            if(k < 10) {
                printf(" 0%d ", k);
            }else {
                printf(" %d ", k);
            }

            *week_day_index+=1;
            j+=1;
            k+=1;

            //Week print finished - move to another one
            if(*week_day_index==8) {
                *week_day_index=1;
                j=1;
                printf("\n"); //Week ended - make a new line for a another one
            }
        }else {
            //We are handling the empty days
            j+=1; //We are moving to a next day in a week
            i--; //We actually didn't print a day number - so we need to decrement and just print a space holder
            printf("    ");
        }
    }
}

int main() {
    int selected_year;
    int selected_starting_day;

    int months_days_number[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *months_names[12] = {"Januar", "Februar", "Marec", "April", "Maj", "Jun", "Jul", "August", "September", "Oktober", "November", "December"};

    //Handle proper year entering
    while(1) {
        char* entered_year = getUsersInput("Zadaj rok, pre ktorý chceš kalendár?");

        //Handle if it's digit only input and non-negative number
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

    //Gap year
    if(selected_year % 4 == 0) {
        months_days_number[1] = 29;
    }

    for(int i=0; i < 12; i++) {
        //Printing months one by one
        print_month(months_names[i], &selected_starting_day, months_days_number[i]);
    }

    printf("\n"); //Just leave a empty line once the program finish.

    return 0;
}