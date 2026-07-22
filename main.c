#include <stdio.h>
#include "expense.h"
#include "file.h"

int main()
{
    loadExpenses();

    int choice;
    do
    {
        printf("\n===============================================================================\n");
        printf("                            PERSONAL EXPENSE TRACKER\n");
        printf("===============================================================================\n");
        printf("\n  [1] Add New Expense\n");
        printf("  [2] View All Expenses\n");
        printf("  [3] View Total Spending Summary\n");
        printf("  [4] Search Expense By ID\n");
        printf("  [5] Delete Expense By ID\n");
        printf("  [6] Exit Application\n");
        printf("\n-------------------------------------------------------------------------------\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a integer.\n");
            while (getchar() != '\n')
                ;
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            if (count >= MAX_EXPENSES)
            {
                printf("Storage is full!\n");
                break;
            }

            addNewExpense();
            break;

        case 2:
            if (count == 0)
            {
                printf("No records to be print.\n");
                break;
            }

            viewAllExpenses();
            break;

        case 3:
            if (count == 0)
            {
                printf("No records to be Calculated.\n");
                break;
            }

            spendSummary();
            break;

        case 4:
            viewExpenseById();
            break;

        case 5:
            deleteExpenseById();
            break;

        case 6:
            printf("Exiting...\n");
            break;

        default:
            printf("Enter a number between 1 and 6.\n");
            break;
        }

    } while (choice != 6);

    return 0;
}