#include <stdio.h>

float celsius_to_fahrenheit(float celsius){
    float fahrenheit = (celsius * 9 / 5) + 32;
    return fahrenheit;
}

int main(){
    printf("Type the temperature in Celsius: ");
    float celsius;
    scanf("%f", &celsius);

    float fahrenheit = celsius_to_fahrenheit(celsius);

    printf("Temperature in Fahrenheit is %f°F", fahrenheit);

    return 0;
}