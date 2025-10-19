#include <stdio.h>

int main(){
    int numbers[3];
    printf("Type the first number:");
    scanf("%d", &numbers[0]);
    printf("Type the second number:");
    scanf("%d", &numbers[1]);
    printf("Type the third number:");
    scanf("%d", &numbers[2]);

    int greater;
    for (int counter = 0; counter < 3; counter++){
        if (numbers[counter] > greater) greater = numbers[counter];
    }

    printf("Greater Number: %d\n", greater);

    return 0;
}