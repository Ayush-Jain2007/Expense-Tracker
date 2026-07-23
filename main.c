#include <stdio.h>
#include "expense.h"
#include "file.h"
#include "utils.h"

struct ExpenseManager manager = {0};

int main()
{
    loadExpenses(&manager);

    int choice, filter_choice, sort_choice;
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
        printf("  [7] Sort Expenses\n");
        printf("  [8] Category Summary\n");
        printf("  [9] View Total Spending Summary\n");
        printf("  [10] Exit Application\n");
        printf("\n-------------------------------------------------------------------------------\n");
        choice = getIntInRange("Enter your choice (1-10): ", 1, 10);

        switch (choice)
        {
        case 1:
            addNewExpense(&manager);
            break;

        case 2:
            viewAllExpenses(&manager);
            break;

        case 3:
            viewExpenseById(&manager);
            break;

        case 4:
            editExpenseById(&manager);
            break;

        case 5:
            deleteExpenseById(&manager);
            break;

        case 6:
            if (manager.count == 0)
            {
                printf("No expense to be Filtered.\n");
                break;
            }

            printf("\n\n===============================================================================\n");
            printf("                                FILTER EXPENSES\n");
            printf("===============================================================================\n");
            printf("\n  [1] Filter Expense By Category\n");
            printf("  [2] Filter Expense By Date\n");
            printf("  [3] Return\n");
            printf("\n-------------------------------------------------------------------------------\n");
            filter_choice = getIntInRange("Enter your choice (1-3): ", 1, 3);

            switch (filter_choice)
            {
            case 1:
                filterExpensesByCategory(&manager);
                break;

            case 2:
                filterExpensesByDate(&manager);
                break;

            case 3:
                printf("Returning...\n");
                break;

            default:
                printf("Please enter between 1 and 3.\n");
                break;
            }

            break;

        case 7:
            if (manager.count == 0)
            {
                printf("No expense to be sort.\n");
                break;
            }

            printf("\n\n===============================================================================\n");
            printf("                                  SORT EXPENSES\n");
            printf("===============================================================================\n");
            printf("\n  [1] Sort By Amount (Low to High)\n");
            printf("  [2] Sort By Amount (High to Low)\n");
            printf("  [3] Sort By Date (Oldest to Newest)\n");
            printf("  [4] Sort By Date (Newest to Oldest)\n");
            printf("  [5] Return\n");
            printf("\n-------------------------------------------------------------------------------\n");
            sort_choice = getIntInRange("Enter your choice (1-5): ", 1, 5);

            switch (sort_choice)
            {
            case 1:
                sortExpensesByAmount(&manager, 1);
                break;

            case 2:
                sortExpensesByAmount(&manager, 0);
                break;

            case 3:
                sortExpensesByDate(&manager, 1);    
                break;

            case 4:
                sortExpensesByDate(&manager, 0);
                break;

            case 5:
                printf("Returning...\n");
                break;

            default:
                printf("Please enter between 1 and 5.\n");
                break;
            }
            break;

        case 8:
            categorySummary(&manager);
            break;

        case 9:
            spendSummary(&manager);
            break;

        case 10:
            printf("Exiting...\n");
            break;

        default:
            printf("Enter a number between 1 and 10.\n");
            break;
        }

    } while (choice != 10);

    return 0;
}