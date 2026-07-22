#include <stdio.h>
#include "expense.h"
#include "file.h"

void loadExpenses(){
    FILE *ptr = fopen("expenses.dat", "rb");

    if (ptr == NULL)
    {
        return;
    }
    
    fread(&count, sizeof(count), 1, ptr);

    if (count < 0 || count > MAX_EXPENSES)
    {
        printf("Invalid expense data!\n");
        count = 0;
        fclose(ptr);
        return;
    }

    fread(expenses, sizeof(struct Expense), count, ptr);

    fclose(ptr);
}

void saveExpenses(){
    FILE *ptr = fopen("expenses.dat", "wb");

    if (ptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    
    fwrite(&count, sizeof(count), 1, ptr);
    fwrite(expenses, sizeof(struct Expense), count, ptr);

    fclose(ptr);
}