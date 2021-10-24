#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

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

char *formatPayment(float num){
    char *convertedFloat;
    convertedFloat=malloc(sizeof(char));
    sprintf(convertedFloat, "%.2f", num);

    printf("This is converted float %s\n\n\n", convertedFloat);

    char formattedString[1000];
    for(int i = 0; i < strlen(convertedFloat); i++){
        int reversedIndex = (strlen(convertedFloat) - 1) - i;
        formattedString[reversedIndex] = convertedFloat[i];
    }
    /*
    for(int i = (strlen(convertedFloat)) - 1; i >= 0; i--){
        int reverseIndex = (strlen(convertedFloat) - i);
        formattedString[reverseIndex] = convertedFloat[i];
    }*/

    printf("This is formatted string %s\n", formattedString);

    return convertedFloat;
}


////////////
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


    int paddedStringLength = ((strlen(str) - (strlen(str) % 3)) / 3) + strlen(str);
    char paddedString[paddedStringLength];
    int extraIndex = 0;

    if(doPadding){
        for(int j = 0; j < strlen(str); j++){
            paddedString[j+extraIndex] = str[j];

            if(j % 2 == 0 && j > 0){
                extraIndex++;
                paddedString[j+extraIndex] = ' ';
            }
        }

        printf("This is my padded string %s \n", paddedString);
    }

    reverse(paddedString, paddedStringLength);
    printf("This is reversed padded string %s \n", paddedString);

	reverse(str, i);
	str[i] = '\0';
	return i;
}

void ftoa(float n, char* res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;

	// Extract floating part
	float fpart = n - (float)ipart;

	// convert integer part to string
	int i = intToStr(ipart, res, 0, 1);

	// check for display option after point
	if (afterpoint != 0) {
		res[i] = ','; // add dot

		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint, 0);
	}
}

// Driver program to test above function
///////////




int main( ) {
	char res[20];
	float n = 13413.2453465;
	ftoa(n, res, 2);
	printf("This is output %s\n", res);
return 0;

formatPayment(1243134.1332);
return 0;

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
