#include <stdio.h>
#include "expense.h"
#include "file.h"

void loadExpenses(struct ExpenseManager *manager)
{
    FILE *ptr = fopen("expenses.dat", "rb");

    if (ptr == NULL)
    {
        return;
    }

    int savedCount;

    if (fread(&savedCount, sizeof(savedCount), 1, ptr) != 1)
    {
        printf("Error reading expense data!\n");
        fclose(ptr);
        return;
    }

    if (savedCount < 0)
    {
        printf("Invalid expense data!\n");
        fclose(ptr);
        return;
    }

    if (!ensureCapacity(manager, savedCount))
    {
        printf("Failed to allocate memory for expenses!\n");
        fclose(ptr);
        return;
    }

    if (fread(manager->expenses,
              sizeof(struct Expense),
              savedCount,
              ptr) != (size_t)savedCount)
    {
        printf("Error reading expense data!\n");
        fclose(ptr);
        return;
    }

    manager->count = savedCount;

    fclose(ptr);
}

void saveExpenses(struct ExpenseManager *manager)
{
    FILE *ptr = fopen("expenses.dat", "wb");

    if (ptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    if (fwrite(&manager->count,
               sizeof(manager->count),
               1,
               ptr) != 1)
    {
        printf("Error writing expense count!\n");
        fclose(ptr);
        return;
    }

    if (fwrite(manager->expenses,
               sizeof(struct Expense),
               manager->count,
               ptr) != (size_t)manager->count)
    {
        printf("Error writing expense data!\n");
        fclose(ptr);
        return;
    }

    fclose(ptr);
}