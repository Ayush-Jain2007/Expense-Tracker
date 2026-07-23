#include <stdio.h>
#include "expense.h"
#include "file.h"

void loadExpenses(struct ExpenseManager *manager){
    FILE *ptr = fopen("expenses.dat", "rb");

    if (ptr == NULL)
    {
        return;
    }
    
    fread(&manager->count, sizeof(manager->count), 1, ptr);

    if (manager->count < 0 || manager->count > MAX_EXPENSES)
    {
        printf("Invalid expense data!\n");
        manager->count = 0;
        fclose(ptr);
        return;
    }

    fread(manager->expenses, sizeof(struct Expense), manager->count, ptr);

    fclose(ptr);
}

void saveExpenses(struct ExpenseManager *manager){
    FILE *ptr = fopen("expenses.dat", "wb");

    if (ptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    
    fwrite(&manager->count, sizeof(manager->count), 1, ptr);
    fwrite(manager->expenses, sizeof(struct Expense), manager->count, ptr);

    fclose(ptr);
}