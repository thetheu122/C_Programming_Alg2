#include <stdio.h>

int main (){
    int n_number;
    printf("Type a number to define how many numbers will be add to the sum: ");
    scanf("%d", &n_number);

    int sum = 0;

    for (int counter = 1; counter <= n_number; counter++)
    {
        int temp_num;
        printf("Type the %d° number: ", counter);
        scanf("%d", &temp_num);
        sum += temp_num;
    }

    printf("Total sum: %d\n", sum);

    return 0;
}