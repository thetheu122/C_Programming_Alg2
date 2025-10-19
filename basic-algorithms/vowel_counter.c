#include <stdio.h>

int main(){
    char string[61];
    char vowels[10] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    printf("Type a word with max. 60 charecters:");
    scanf("%s", string);

    int vowels_counter = 0;
    int string_lenght = sizeof(string) / sizeof(string[0]);
    for (int counter = 0; string[counter] != '\0'; counter++)
    {
        for (int i = 0; i < 10; i++)
        {
            if(string[counter] == vowels[i]){
                vowels_counter++;
                break;
            }
                
        }
    }

    printf("Total vowals: %d\n", vowels_counter);

    return 0;
}
