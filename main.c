#include <stdio.h>
#include "expense.h"
#include "file.h"

int main()
{
    loadExpenses();

    int choice, filter_choice;
    do
    {
        printf("\n===============================================================================\n");
        printf("                            PERSONAL EXPENSE TRACKER\n");
        printf("===============================================================================\n");
        printf("\n  [1] Add New Expense\n");
        printf("  [2] View All Expenses\n");
        printf("  [3] View Expense By ID\n");
        printf("  [4] Edit Expense\n");
        printf("  [5] Delete Expense\n");
        printf("  [6] Filter Expense\n");
        printf("  [7] View Total Spending Summary\n");
        printf("  [8] Exit Application\n");
        printf("\n-------------------------------------------------------------------------------\n");
        printf("Enter your choice (1-8): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a integer.\n");
            clearInputBuffer();
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            addNewExpense();
            break;

        case 2:
            viewAllExpenses();
            break;

        case 3:
            viewExpenseById();
            break;

        case 4:
            editExpenseById();
            break;

        case 5:
            deleteExpenseById();
            break;

        case 6:
            printf("\n\n===============================================================================\n");
            printf("                                FILTER EXPENSE\n");
            printf("===============================================================================\n");
            printf("\n  [1] Filter Expense By Category\n");
            printf("  [2] Filter Expense By Date\n");
            printf("  [3] Return\n");
            printf("\n-------------------------------------------------------------------------------\n");
            printf("Enter your choice (1-3): ");
            
            if (scanf("%d", &filter_choice) != 1)
            {
                printf("Invalid input! Please enter a integer.\n");
                clearInputBuffer();
                filter_choice = 0;
            }

            switch (filter_choice)
            {
            case 1:
                filterExpensesByCategory();
                break;
            
            case 2:
                filterExpensesByDate();
                break;
            
            case 3:
                printf("Returning...\n");
                break;
            
            default:
                printf("Please enter between 1 and 3!\n");
                break;
            }

            break;

        case 7:
            spendSummary();
            break;

        case 8:
            printf("Exiting...\n");
            break;

        default:
            printf("Enter a number between 1 and 8.\n");
            break;
        }

    } while (choice != 8);

    return 0;
}