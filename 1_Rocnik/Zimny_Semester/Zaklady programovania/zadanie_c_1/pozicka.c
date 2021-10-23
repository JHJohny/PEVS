#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *getUsersInput()
{
    char *ch1;
    ch1=malloc(sizeof(char));

    printf( "Zadaj sumu, ktorú si chceš požičať:");
    scanf("%s", ch1);

    return ch1;
}

int isDigitOnly(const char *s)
{
    for (int i = 0; i < strlen(s); i++) {
        if(isdigit(s[i]) == 0){
            if(!(s[i] == '.' || s[i] == ',')){
                return 0;
            }
        }
    }

    return 1;
}

float getFirstPayment(float num){
    if(num < 20000){
        return (num / 100);
    }else if(num < 50000){
        return (((num / 100) * 2) + 200);
    }else if(num <= 150000){
        return (((num / 100) * 3) + 800);
    }else{
        return -1;
    }
}

int main( ) {
    char *userInput;
    userInput = getUsersInput();

    if(isDigitOnly(userInput)){
        float userInputNumber = atof(userInput);
        float payment = getFirstPayment(atof(userInput));

        if(payment > 0){
            printf("Pri schválení pôžičky na %.2f EUR je potrebné zaplatiť prvú splátku: %.2f EUR.\n", userInputNumber, payment);
        }

    }else{
        printf( "And it's NOT digit only\n");
    }

    return 0;
}
