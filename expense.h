#ifndef EXPENSE_H
#define EXPENSE_H

#define MAX_EXPENSES 100

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
    long amount;
    struct Date date;
};

struct ExpenseManager
{
    struct Expense expenses[MAX_EXPENSES];
    int count;
};


int isValidDate(int day, int month, int year);
int findExpenseById(struct ExpenseManager *manager, int id);
void displayExpense(struct Expense *expense);
void displayExpenseTableHeader(void);
void displayExpenseTableLine(void);

void addNewExpense(struct ExpenseManager *manager);
void viewAllExpenses(struct ExpenseManager *manager);
void spendSummary(struct ExpenseManager *manager);
void viewExpenseById(struct ExpenseManager *manager);
void deleteExpenseById(struct ExpenseManager *manager);
void editExpenseById(struct ExpenseManager *manager);
void filterExpensesByCategory(struct ExpenseManager *manager);
void filterExpensesByDate(struct ExpenseManager *manager);
void sortExpensesByAmount(struct ExpenseManager *manager, int ascending);
void sortExpensesByDate(struct ExpenseManager *manager, int ascending);
void categorySummary(struct ExpenseManager *manager);

#endif