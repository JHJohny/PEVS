#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

char *getUsersInput()
{
    /*
    This function ask user for an input

    Function uses a string parameter and allocate memory for it by calling a function malloc.
    For reading user input uses a scanf function.
    */
    char *ch1;
    ch1=malloc(sizeof(char));

    printf( "Zadaj sumu, ktorú si chceš požičať:");
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

double getFirstPayment(double num){
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

char *formatPayment(float num){
    char *convertedFloat;
    convertedFloat=malloc(sizeof(char));
    sprintf(convertedFloat, "%.2f", num);

    char formattedString[1000];
    for(int i = 0; i < strlen(convertedFloat); i++){
        int reversedIndex = (strlen(convertedFloat) - 1) - i;
        formattedString[reversedIndex] = convertedFloat[i];
    }

    return convertedFloat;
}

void reverse(char* str, int len)
{
	int i = 0, j = strlen(str) - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int intToStr(int x, char str[], int d, int doPadding)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	while (i < d)
		str[i++] = '0';

    int paddedStringLength = 500;
    char paddedString[paddedStringLength];
    int extraIndex = 0;

    if(doPadding){
        for(int j = 0; j < strlen(str); j++){
            paddedString[j+extraIndex] = str[j];

            if((j+1) % 3 == 0 && j > 0){
                extraIndex++;
                paddedString[j+extraIndex] = ' ';
            }
        }

        for(int k = 0; k < strlen(paddedString); k++){
            str[k] = paddedString[k];
        }
    }

	reverse(str, i);

	return strlen(str);
}

void floatToString(double n, char* res, int afterpoint)
{
	int ipart = (int)n;
	double fpart = n - (double)ipart;
	int i = intToStr(ipart, res, 0, 1);

	if (afterpoint != 0) {
		res[i] = ',';

		fpart = fpart * pow(10, afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint, 0);
	}
}

int main( ) {
/*
	char res[50];
	double n = 1341352350.235245;
	floatToString(n, res, 2);
	printf("This is output %s\n", res);
return 0;
*/
    char *userInput;
    userInput = getUsersInput();

    if(isDigitOnly(userInput)){
        double userInputNumber = strtod(userInput, NULL);
        double payment = getFirstPayment(userInputNumber);

        char formattedLoan[50];
        floatToString(userInputNumber, formattedLoan, 2);

        char formattedPayment[50];
        floatToString(payment, formattedPayment, 2);

        if(payment > 0){
            printf("Pri schválení pôžičky na %s EUR je potrebné zaplatiť prvú splátku: %s EUR.\n", formattedLoan, formattedPayment);
        }else{
            printf("Banka neschvaluje pôžičky nad 150 000 EUR\n");
        }

    }else{
        printf("Nespravna suma, prosim zadaj sumu v spravnom tvare.\n");
    }

    return 0;
}
