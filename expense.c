#include <stdio.h>
#include <string.h>
#include "expense.h"
#include "file.h"
#include "utils.h"

int count = 0;
struct Expense expenses[MAX_EXPENSES];

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

int findExpenseById(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (id == expenses[i].id)
        {
            return i;
        }
    }
    return -1;
}

void addNewExpense()
{
    if (count >= MAX_EXPENSES)
    {
        printf("Storage is full!\n");
        return;
    }

    // Removing leftover \n
    clearInputBuffer();

    // Setting id
    expenses[count].id = count + 1920;

    // Get Desription
    printf("Enter Desription: ");
    fgets(expenses[count].description, 50, stdin);
    expenses[count].description[strcspn(expenses[count].description, "\n")] = '\0';

    // Get Category
    printf("Enter Category: ");
    fgets(expenses[count].category, 50, stdin);
    expenses[count].category[strcspn(expenses[count].category, "\n")] = '\0';

    // Get Amount
    expenses[count].amount = getFloat("Enter Amount: ");

    if (expenses[count].amount <= 0)
    {
        printf("Amount must be greater than 0!\n");
        return;
    }

    // Get Date
    expenses[count].date.day = getInt("Enter Day: ");
    expenses[count].date.month = getInt("Enter Month: ");
    expenses[count].date.year = getInt("Enter Year: ");

    if (!isValidDate(expenses[count].date.day, expenses[count].date.month, expenses[count].date.year))
    {
        printf("Invalid Date!\n");
        return;
    }

    count++;
    saveExpenses();
}

void viewAllExpenses()
{
    if (count == 0)
    {
        printf("No records to be print.\n");
        return;
    }
    printf("===============================================================================\n");
    printf("                                  ALL EXPENSES\n");
    printf("===============================================================================\n");
    printf("%-6s | %-10s | %-15s | %-25s | %-10s\n", "ID", "Date", "Category", "Description", "Amount ($)");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-6d | %02d/%02d/%-4d | %-15s | %-25s | $%-9.2f\n",
               expenses[i].id,
               expenses[i].date.day, expenses[i].date.month, expenses[i].date.year,
               expenses[i].category,
               expenses[i].description,
               expenses[i].amount);
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void spendSummary()
{
    if (count == 0)
    {
        printf("No records to be Calculated.\n");
        return;
    }

    float total_spent = 0, average_cost = 0;
    int max_index = 0, min_index = 0;

    for (int i = 0; i < count; i++)
    {
        total_spent += expenses[i].amount;
        if (expenses[i].amount > expenses[max_index].amount)
        {
            max_index = i;
        }
        if (expenses[i].amount < expenses[min_index].amount)
        {
            min_index = i;
        }
    }

    average_cost = (float)total_spent / count;
    printf("==================================================\n");
    printf("                FINANCIAL OVERVIEW\n");
    printf("==================================================\n\n");
    printf("  +----------------------------------------------+\n");

    printf("  |  TOTAL SPENT :%8.2f                       |\n", total_spent);
    printf("  |  TOTAL ITEMS :%6d                         |\n", count);
    printf("  |  AVERAGE COST:%8.2f/item                  |\n", average_cost);

    printf("  +----------------------------------------------+\n");
    printf("\n  [!] Largest Expense :  %-5.2f (%s)\n", expenses[max_index].amount, expenses[max_index].description);
    printf("  [*] Smallest Expense:  %-5.2f (%s)\n", expenses[min_index].amount, expenses[min_index].description);
    printf("\n==================================================\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void viewExpenseById()
{
    int id;

    id = getInt("Enter ID: ");

    int index = findExpenseById(id);
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
               expenses[index].id,
               expenses[index].date.day, expenses[index].date.month, expenses[index].date.year,
               expenses[index].category,
               expenses[index].description,
               expenses[index].amount);
        printf("-------------------------------------------------------------------------------\n\n");
        printf("Press Enter to continue...");
        getchar();
        getchar();
    }
}

void deleteExpenseById()
{
    int id;

    if (count == 0)
    {
        printf("No Data to be deleted.\n");
        return;
    }

    id = getInt("Enter ID: ");

    int index = findExpenseById(id);
    if (index == -1)
    {
        printf("ID doesn't exists!\n");
        return;
    }
    else
    {
        for (int j = index; j < (count - 1); j++)
        {
            expenses[j] = expenses[j + 1];
        }
    }
    count--;

    saveExpenses();

    printf("Expense Deleted Successfully!\n");
}

void editExpenseById(void)
{
    int id, day, month, year;
    float amount;

    if (count == 0)
    {
        printf("No expenses to edit.\n");
        return;
    }

    id = getInt("Enter ID: ");

    int index = findExpenseById(id);

    if (index == -1)
    {
        printf("Expense with ID %d not found!\n", id);
        return;
    }
    else
    {
        clearInputBuffer();
        printf("Enter new Description: ");
        fgets(expenses[index].description, 50, stdin);
        expenses[index].description[strcspn(expenses[index].description, "\n")] = '\0';

        printf("Enter new Category: ");
        fgets(expenses[index].category, 50, stdin);
        expenses[index].category[strcspn(expenses[index].category, "\n")] = '\0';

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
        expenses[index].amount = amount;
        expenses[index].date.day = day;
        expenses[index].date.month = month;
        expenses[index].date.year = year;
    }

    saveExpenses();

    printf("Expenses Updated Successfully!\n");
}

void filterExpensesByCategory()
{
    char input_category[50];
    int found = 0;

    if (count == 0)
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

    for (int i = 0; i < count; i++)
    {
        if (strcmp(input_category, expenses[i].category) == 0)
        {
            printf("%-6d | %02d/%02d/%-4d | %-15s | %-25s | $%-9.2f\n",
                   expenses[i].id,
                   expenses[i].date.day, expenses[i].date.month, expenses[i].date.year,
                   expenses[i].category,
                   expenses[i].description,
                   expenses[i].amount);
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

void filterExpensesByDate()
{
    int month, year, found = 0;
    if (count == 0)
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

    for (int i = 0; i < count; i++)
    {
        if (month == expenses[i].date.month && year == expenses[i].date.year)
        {
            printf("%-6d | %02d/%02d/%-4d | %-15s | %-25s | $%-9.2f\n",
                   expenses[i].id,
                   expenses[i].date.day, expenses[i].date.month, expenses[i].date.year,
                   expenses[i].category,
                   expenses[i].description,
                   expenses[i].amount);
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

void sortExpensesByAmount(int ascending)
{
    struct Expense temp;

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (ascending && expenses[i].amount > expenses[j].amount)
            {
                temp = expenses[i];
                expenses[i] = expenses[j];
                expenses[j] = temp;
            }
            else if (!ascending && expenses[i].amount < expenses[j].amount)
            {
                temp = expenses[i];
                expenses[i] = expenses[j];
                expenses[j] = temp;
            }
        }
    }

    saveExpenses();
    printf("Expenses sorted successfully!\n");
}

void sortExpensesByDate(int ascending)
{
    struct Expense temp;

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int swap = 0;

            if (ascending)
            {
                if (expenses[i].date.year > expenses[j].date.year)
                {
                    swap = 1;
                }
                else if (expenses[i].date.year == expenses[j].date.year &&
                         expenses[i].date.month > expenses[j].date.month)
                {
                    swap = 1;
                }
                else if (expenses[i].date.year == expenses[j].date.year &&
                         expenses[i].date.month == expenses[j].date.month &&
                         expenses[i].date.day > expenses[j].date.day)
                {
                    swap = 1;
                }
            }

            else
            {
                if (expenses[i].date.year < expenses[j].date.year)
                {
                    swap = 1;
                }
                else if (expenses[i].date.year == expenses[j].date.year &&
                         expenses[i].date.month < expenses[j].date.month)
                {
                    swap = 1;
                }
                else if (expenses[i].date.year == expenses[j].date.year &&
                         expenses[i].date.month == expenses[j].date.month &&
                         expenses[i].date.day < expenses[j].date.day)
                {
                    swap = 1;
                }
            }

            if (swap)
            {
                temp = expenses[i];
                expenses[i] = expenses[j];
                expenses[j] = temp;
            }
        }
    }

    saveExpenses();
    printf("Expenses sorted successfully!\n");
}

void categorySummary(void)
{
    char categories[MAX_EXPENSES][50];
    float categoryTotals[MAX_EXPENSES] = {0};
    int categoryCounts[MAX_EXPENSES] = {0};
    int categoryCount = 0;

    for (int i = 0; i < count; i++)
    {
        int found = -1;

        for (int j = 0; j < categoryCount; j++)
        {
            if (strcmp(expenses[i].category, categories[j]) == 0)
            {
                found = j;
                break;
            }
        }

        if (found != -1)
        {
            categoryTotals[found] += expenses[i].amount;
            categoryCounts[found]++;
        }
        else
        {
            strcpy(categories[categoryCount], expenses[i].category);
            categoryTotals[categoryCount] = expenses[i].amount;
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