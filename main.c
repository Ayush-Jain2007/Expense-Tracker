#include <stdio.h>
#include <string.h>

#define MAX_EXPENSES 100
int count = 0;

struct Date
{
    int day;
    int month;
    int year;
};

struct Expense
{
    int id;
    char description[50];
    char category[50];
    float amount;
    struct Date date;
};

struct Expense expenses[MAX_EXPENSES];

int isValidDate(int day, int month, int year);
int isValidDate(int day, int month, int year){
    int daysInMonth[] = {
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31
    };
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
    if (day < 1 || day > daysInMonth[month-1])
    {
        return 0;
    }
    
    return 1;
}

void addNewExpenses();
void addNewExpenses()
{
    // Removing leftover \n
    while (getchar() != '\n')
        ;

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
    printf("Enter Amount: ");
    if (scanf("%f", &expenses[count].amount) != 1)
    {
        printf("Invalid Amount!\n");
        while (getchar() != '\n')
            ;
        return;
    }
    if (expenses[count].amount <= 0)
    {
        printf("Amount must be greater than 0!\n");
        return;
    }

    // Get Date
    printf("Enter Day: ");
    if (scanf("%d", &expenses[count].date.day) != 1)
    {
        printf("Invalid Date!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    printf("Enter Month: ");
    if (scanf("%d", &expenses[count].date.month) != 1)
    {
        printf("Invalid Month!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    printf("Enter year: ");
    if (scanf("%d", &expenses[count].date.year) != 1)
    {
        printf("Invalid Year!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    if (!isValidDate(expenses[count].date.day, expenses[count].date.month, expenses[count].date.year))
    {
        printf("Invalid Date!\n");
        return;
    }

    count++;
}

void viewAllExpenses();
void viewAllExpenses()
{
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
}

void spendSummary();
void spendSummary()
{
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

    printf("  |  TOTAL SPENT :   %10.2f                     |\n", total_spent);
    printf("  |  TOTAL ITEMS :   %10d                     |\n", count);
    printf("  |  AVERAGE COST:   %10.2f/item                |\n", average_cost);

    printf("  +----------------------------------------------+\n");
    printf("\n  [!] Largest Expense :  %-5.2f (%s)\n", expenses[max_index].amount, expenses[max_index].description);
    printf("  [*] Smallest Expense:  %-5.2f (%s)\n", expenses[min_index].amount, expenses[min_index].description);
    printf("\n==================================================\n");
}

int main()
{
    int choice;
    do
    {
        printf("===============================================================================\n");
        printf("                            PERSONAL EXPENSE TRACKER\n");
        printf("===============================================================================\n");
        printf("\n  [1] Add New Expense\n");
        printf("  [2] View All Expenses\n");
        printf("  [3] View Total Spending Summary\n");
        printf("  [4] Exit Application\n");
        printf("\n-------------------------------------------------------------------------------\n");
        printf("Enter your choice (1-4): ");

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

            addNewExpenses();
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
            printf("Exiting...\n");
            break;

        default:
            printf("Enter a number between 1 and 4.\n");
            break;
        }

    } while (choice != 4);

    return 0;
}