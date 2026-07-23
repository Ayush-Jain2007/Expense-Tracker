#include <stdio.h>
#include <string.h>
#include "expense.h"
#include "file.h"
#include "utils.h"

int isValidDate(int day, int month, int year)
{
    int daysInMonth[] = {
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31};
    if (day < 1 || day > 31)
    {
        printf("Day must be between 1 and 31!\n");
        return 0;
    }
    if (month < 1 || month > 12)
    {
        printf("Month must be between 1 and 12!\n");
        return 0;
    }
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
    {
        daysInMonth[1] = 29;
    }
    if (day < 1 || day > daysInMonth[month - 1])
    {
        printf("Invalid day for the selected month!\n");
        return 0;
    }

    return 1;
}

int findExpenseById(struct ExpenseManager *manager,int id)
{
    for (int i = 0; i < manager->count; i++)
    {
        if (id == manager->expenses[i].id)
        {
            return i;
        }
    }
    return -1;
}

void addNewExpense(struct ExpenseManager *manager)
{
    if (manager->count >= MAX_EXPENSES)
    {
        printf("Storage is full!\n");
        return;
    }

    // Removing leftover \n
    clearInputBuffer();

    // Setting id
    manager->expenses[manager->count].id = manager->count + 1920;

    // Get Desription
    printf("Enter Desription: ");
    fgets(manager->expenses[manager->count].description, 50, stdin);
    manager->expenses[manager->count].description[strcspn(manager->expenses[manager->count].description, "\n")] = '\0';

    // Get Category
    printf("Enter Category: ");
    fgets(manager->expenses[manager->count].category, 50, stdin);
    manager->expenses[manager->count].category[strcspn(manager->expenses[manager->count].category, "\n")] = '\0';

    // Get Amount
    manager->expenses[manager->count].amount = getFloat("Enter Amount: ");

    if (manager->expenses[manager->count].amount <= 0)
    {
        printf("Amount must be greater than 0!\n");
        return;
    }

    // Get Date
    manager->expenses[manager->count].date.day = getInt("Enter Day: ");
    manager->expenses[manager->count].date.month = getInt("Enter Month: ");
    manager->expenses[manager->count].date.year = getInt("Enter Year: ");

    if (!isValidDate(manager->expenses[manager->count].date.day, manager->expenses[manager->count].date.month, manager->expenses[manager->count].date.year))
    {
        printf("Invalid Date!\n");
        return;
    }

    manager->count++;
    saveExpenses(manager);
}

void viewAllExpenses(struct ExpenseManager *manager)
{
    if (manager->count == 0)
    {
        printf("No records to be print.\n");
        return;
    }
    printf("===============================================================================\n");
    printf("                                  ALL EXPENSES\n");
    printf("===============================================================================\n");
    printf("%-6s | %-10s | %-15s | %-25s | %-10s\n", "ID", "Date", "Category", "Description", "Amount ($)");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < manager->count; i++)
    {
        printf("%-6d | %02d/%02d/%-4d | %-15s | %-25s | $%-9.2f\n",
                manager->expenses[i].id,
                manager->expenses[i].date.day, 
                manager->expenses[i].date.month,
                manager->expenses[i].date.year,
                manager->expenses[i].category,
                manager->expenses[i].description,
                manager->expenses[i].amount);
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void spendSummary(struct ExpenseManager *manager)
{
    if (manager->count == 0)
    {
        printf("No records to be Calculated.\n");
        return;
    }

    float total_spent = 0, average_cost = 0;
    int max_index = 0, min_index = 0;

    for (int i = 0; i < manager->count; i++)
    {
        total_spent += manager->expenses[i].amount;
        if (manager->expenses[i].amount > manager->expenses[max_index].amount)
        {
            max_index = i;
        }
        if (manager->expenses[i].amount < manager->expenses[min_index].amount)
        {
            min_index = i;
        }
    }

    average_cost = (float)total_spent / manager->count;
    printf("==================================================\n");
    printf("                FINANCIAL OVERVIEW\n");
    printf("==================================================\n\n");
    printf("  +----------------------------------------------+\n");

    printf("  |  TOTAL SPENT :%10.2f                     |\n", total_spent);
    printf("  |  TOTAL ITEMS :%6d                         |\n", manager->count);
    printf("  |  AVERAGE COST:%10.2f/item                |\n", average_cost);

    printf("  +----------------------------------------------+\n");
    printf("\n  [!] Largest Expense :  %-5.2f (%s)\n", manager->expenses[max_index].amount, manager->expenses[max_index].description);
    printf("  [*] Smallest Expense:  %-5.2f (%s)\n", manager->expenses[min_index].amount, manager->expenses[min_index].description);
    printf("\n==================================================\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void viewExpenseById(struct ExpenseManager *manager)
{
    int id;

    id = getInt("Enter ID: ");

    int index = findExpenseById(manager, id);
    if (index == -1)
    {
        printf("ID doesn't exists!\n");
        return;
    }
    else
    {
        printf("===============================================================================\n");
        printf("                                 EXPENSE BY ID\n");
        printf("===============================================================================\n");
        printf("%-6s | %-10s | %-15s | %-25s | %-10s\n", "ID", "Date", "Category", "Description", "Amount ($)");
        printf("-------------------------------------------------------------------------------\n");
        printf("%-6d | %02d/%02d/%-4d | %-15s | %-25s | $%-9.2f\n",
               manager->expenses[index].id,
               manager->expenses[index].date.day, manager->expenses[index].date.month, manager->expenses[index].date.year,
               manager->expenses[index].category,
               manager->expenses[index].description,
               manager->expenses[index].amount);
        printf("-------------------------------------------------------------------------------\n\n");
        printf("Press Enter to continue...");
        getchar();
        getchar();
    }
}

void deleteExpenseById(struct ExpenseManager *manager)
{
    int id;

    if (manager->count == 0)
    {
        printf("No Data to be deleted.\n");
        return;
    }

    id = getInt("Enter ID: ");

    int index = findExpenseById(manager, id);
    if (index == -1)
    {
        printf("ID doesn't exists!\n");
        return;
    }
    else
    {
        for (int j = index; j < (manager->count - 1); j++)
        {
            manager->expenses[j] = manager->expenses[j + 1];
        }
    }
    manager->count--;

    saveExpenses(manager);

    printf("Expense Deleted Successfully!\n");
}

void editExpenseById(struct ExpenseManager *manager)
{
    int id, day, month, year;
    float amount;

    if (manager->count == 0)
    {
        printf("No expenses to edit.\n");
        return;
    }

    id = getInt("Enter ID: ");

    int index = findExpenseById(manager, id);

    if (index == -1)
    {
        printf("Expense with ID %d not found!\n", id);
        return;
    }
    else
    {
        clearInputBuffer();
        printf("Enter new Description: ");
        fgets(manager->expenses[index].description, 50, stdin);
        manager->expenses[index].description[strcspn(manager->expenses[index].description, "\n")] = '\0';

        printf("Enter new Category: ");
        fgets(manager->expenses[index].category, 50, stdin);
        manager->expenses[index].category[strcspn(manager->expenses[index].category, "\n")] = '\0';

        amount = getFloat("Enter Amount: ");

        if (amount <= 0)
        {
            printf("Amount should be greater than 0.\n");
            return;
        }

        day = getInt("Enter Day: ");

        month = getInt("Enter Month: ");

        year = getInt("Enter Year: ");

        if (!isValidDate(day, month, year))
        {
            printf("Invalid Date!\n");
            return;
        }
        manager->expenses[index].amount = amount;
        manager->expenses[index].date.day = day;
        manager->expenses[index].date.month = month;
        manager->expenses[index].date.year = year;
    }

    saveExpenses(manager);

    printf("Expenses Updated Successfully!\n");
}

void filterExpensesByCategory(struct ExpenseManager *manager)
{
    char input_category[50];
    int found = 0;

    if (manager->count == 0)
    {
        printf("No category to be filtered.\n");
        return;
    }

    printf("===============================================================================\n");
    printf("                          FILTER EXPENSE BY CATEGORY\n");
    printf("===============================================================================\n");
    printf("\nEnter Category: ");
    clearInputBuffer();

    fgets(input_category, 50, stdin);
    input_category[strcspn(input_category, "\n")] = '\0';

    for (int i = 0; i < manager->count; i++)
    {
        if (strcmp(input_category, manager->expenses[i].category) == 0)
        {
            printf("%-6d | %02d/%02d/%-4d | %-15s | %-25s | $%-9.2f\n",
                   manager->expenses[i].id,
                   manager->expenses[i].date.day, manager->expenses[i].date.month, manager->expenses[i].date.year,
                   manager->expenses[i].category,
                   manager->expenses[i].description,
                   manager->expenses[i].amount);
            found++;
        }
    }
    if (found == 0)
    {
        printf("\nNo Expense found with those category!\n");
        return;
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("\nTotal %d expenses found!\n", found);
}

void filterExpensesByDate(struct ExpenseManager *manager)
{
    int month, year, found = 0;
    if (manager->count == 0)
    {
        printf("No expenses to filter.\n");
        return;
    }

    printf("===============================================================================\n");
    printf("                            FILTER EXPENSE BY DATE\n");
    printf("===============================================================================\n");
    printf("Enter Month: ");
    if (scanf("%d", &month) != 1)
    {
        printf("Invalid Month!\n");
        clearInputBuffer();
        return;
    }
    if (month < 1 || month > 12)
    {
        printf("Month must be between 1 and 12!\n");
        return;
    }

    printf("Enter Year: ");
    if (scanf("%d", &year) != 1)
    {
        printf("Invalid Year!\n");
        clearInputBuffer();
        return;
    }
    if (year < 1 || year > 3000)
    {
        printf("Year must be between 1 and 3000!\n");
        return;
    }

    for (int i = 0; i < manager->count; i++)
    {
        if (month == manager->expenses[i].date.month && year == manager->expenses[i].date.year)
        {
            printf("%-6d | %02d/%02d/%-4d | %-15s | %-25s | $%-9.2f\n",
                   manager->expenses[i].id,
                   manager->expenses[i].date.day, manager->expenses[i].date.month, manager->expenses[i].date.year,
                   manager->expenses[i].category,
                   manager->expenses[i].description,
                   manager->expenses[i].amount);
            found++;
        }
    }
    if (found == 0)
    {
        printf("\nNo Expense found with those Date!\n");
        return;
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("\nTotal %d expenses found!\n", found);
}

void sortExpensesByAmount(struct ExpenseManager *manager, int ascending)
{
    struct Expense temp;

    for (int i = 0; i < manager->count - 1; i++)
    {
        for (int j = i + 1; j < manager->count; j++)
        {
            if (ascending && manager->expenses[i].amount > manager->expenses[j].amount)
            {
                temp = manager->expenses[i];
                manager->expenses[i] = manager->expenses[j];
                manager->expenses[j] = temp;
            }
            else if (!ascending && manager->expenses[i].amount < manager->expenses[j].amount)
            {
                temp = manager->expenses[i];
                manager->expenses[i] = manager->expenses[j];
                manager->expenses[j] = temp;
            }
        }
    }

    saveExpenses(manager);
    printf("Expenses sorted successfully!\n");
}

void sortExpensesByDate(struct ExpenseManager *manager, int ascending)
{
    struct Expense temp;

    for (int i = 0; i < manager->count - 1; i++)
    {
        for (int j = i + 1; j < manager->count; j++)
        {
            int swap = 0;

            if (ascending)
            {
                if (manager->expenses[i].date.year > manager->expenses[j].date.year)
                {
                    swap = 1;
                }
                else if (manager->expenses[i].date.year == manager->expenses[j].date.year &&
                         manager->expenses[i].date.month > manager->expenses[j].date.month)
                {
                    swap = 1;
                }
                else if (manager->expenses[i].date.year == manager->expenses[j].date.year &&
                         manager->expenses[i].date.month == manager->expenses[j].date.month &&
                         manager->expenses[i].date.day > manager->expenses[j].date.day)
                {
                    swap = 1;
                }
            }

            else
            {
                if (manager->expenses[i].date.year < manager->expenses[j].date.year)
                {
                    swap = 1;
                }
                else if (manager->expenses[i].date.year == manager->expenses[j].date.year &&
                         manager->expenses[i].date.month < manager->expenses[j].date.month)
                {
                    swap = 1;
                }
                else if (manager->expenses[i].date.year == manager->expenses[j].date.year &&
                         manager->expenses[i].date.month == manager->expenses[j].date.month &&
                         manager->expenses[i].date.day < manager->expenses[j].date.day)
                {
                    swap = 1;
                }
            }

            if (swap)
            {
                temp = manager->expenses[i];
                manager->expenses[i] = manager->expenses[j];
                manager->expenses[j] = temp;
            }
        }
    }

    saveExpenses(manager);
    printf("Expenses sorted successfully!\n");
}

void categorySummary(struct ExpenseManager *manager)
{
    char categories[MAX_EXPENSES][50];
    float categoryTotals[MAX_EXPENSES] = {0};
    int categoryCounts[MAX_EXPENSES] = {0};
    int categoryCount = 0;

    for (int i = 0; i < manager->count; i++)
    {
        int found = -1;

        for (int j = 0; j < categoryCount; j++)
        {
            if (strcmp(manager->expenses[i].category, categories[j]) == 0)
            {
                found = j;
                break;
            }
        }

        if (found != -1)
        {
            categoryTotals[found] += manager->expenses[i].amount;
            categoryCounts[found]++;
        }
        else
        {
            strcpy(categories[categoryCount], manager->expenses[i].category);
            categoryTotals[categoryCount] = manager->expenses[i].amount;
            categoryCounts[categoryCount] = 1;
            categoryCount++;
        }
    }

    printf("\n==================================================\n");
    printf("                 CATEGORY SUMMARY\n");
    printf("==================================================\n");
    printf("%-20s | %-10s | %-15s\n",
           "Category", "Expenses", "Total Spent");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < categoryCount; i++)
    {
        printf("%-20s | %-10d | $%-14.2f\n",
               categories[i],
               categoryCounts[i],
               categoryTotals[i]);
    }

    printf("--------------------------------------------------\n");
}