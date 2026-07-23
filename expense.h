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
    float amount;
    struct Date date;
};

extern int count;
extern struct Expense expenses[MAX_EXPENSES];

int isValidDate(int day, int month, int year);
int findExpenseById(int id);
void clearInputBuffer(void);

void addNewExpense(void);
void viewAllExpenses(void);
void spendSummary(void);
void viewExpenseById(void);
void deleteExpenseById(void);
void editExpenseById(void);
void filterExpensesByCategory(void);
void filterExpensesByDate(void);

#endif