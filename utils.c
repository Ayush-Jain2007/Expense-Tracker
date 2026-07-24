#include <stdio.h>
#include "expense.h"
#include "file.h"
#include "utils.h"

void clearInputBuffer()
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF)
        ;
}

int getInt(const char *prompt){
    int value;

    while (1)
    {
        printf("%s", prompt);

        if (scanf("%d", &value) == 1)
        {
            clearInputBuffer();
            return value;
        }
        
        printf("Invalid Input! Please enter a number.\n");
        clearInputBuffer();
    }
    
}

int getIntInRange(const char *prompt, int min, int max){
    int value;

    while (1)
    {
        value = getInt(prompt);

        if (value >= min && value <= max)
        {
            return value;
        }
        
        printf("Please enter a number between %d and %d.\n", min, max);
    }
}

float getFloat(const char *prompt)
{
    float value;

    while (1)
    {
        printf("%s", prompt);

        if (scanf("%f", &value) == 1)
        {
            clearInputBuffer();
            return value;
        }

        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
    }
}

void pauseScreen(void)
{
    printf("\nPress Enter to continue...");
    clearInputBuffer();
    getchar();
}