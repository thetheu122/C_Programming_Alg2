#include <stdio.h>

int main(){
    int number;
    printf("Type a number: ");
    scanf("%d", &number);

    for (int counter = 1; counter <= 10;counter++){
        printf("%d x %d = %d\n", number, counter, number * counter);
    }

    return 0;
}