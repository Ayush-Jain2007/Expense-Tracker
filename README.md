# Personal Expense Tracker

A console-based personal expense tracker written in **C**. This project allows users to record, view, and analyze their daily expenses through a simple terminal interface.

The project was built to practice core C programming concepts such as structures, arrays, functions, input handling, and modular program design.

---

## Features

* Add new expenses
* Automatically generate a unique expense ID
* Store:

  * Expense description
  * Expense category
  * Amount
  * Date
* View all recorded expenses in a formatted table
* Calculate a spending summary
* Display:

  * Total amount spent
  * Total number of expenses
  * Average expense amount
  * Largest expense
  * Smallest expense
* Input validation for numeric values
* Supports up to **100 expenses**

---

## Technologies Used

* **Language:** C
* **Standard:** C99
* **Libraries:**

  * `stdio.h`
  * `string.h`

---

## Project Structure

```text
expense-tracker/
│
├── main.c
└── README.md
```

> The current version is implemented in a single C source file. The project can later be refactored into multiple files as it grows.

---

## Data Structure

Each expense is represented using a `struct Expense`.

```c
struct Expense
{
    int id;
    char description[50];
    char category[50];
    float amount;
    struct Date date;
};
```

The date is stored using a separate structure:

```c
struct Date
{
    int day;
    int month;
    int year;
};
```

This demonstrates the use of **nested structures** in C.

---

## How to Compile

Using GCC:

```bash
gcc main.c -o expense_tracker
```

---

## How to Run

### Windows

```bash
expense_tracker.exe
```

### Linux / macOS

```bash
./expense_tracker
```

---

## Usage

After starting the program, the following menu is displayed:

```text
===============================================================================
                            PERSONAL EXPENSE TRACKER
===============================================================================

  [1] Add New Expense
  [2] View All Expenses
  [3] View Total Spending Summary
  [4] Exit Application
```

### 1. Add New Expense

Enter the following information:

```text
Enter Description: Grocery Shopping
Enter Category: Food
Enter Amount: 1250.50
Enter Day: 21
Enter Month: 7
Enter Year: 2026
```

The expense is then stored in memory.

---

### 2. View All Expenses

Displays all recorded expenses in a formatted table:

```text
ID     | Date       | Category        | Description               | Amount ($)
-------------------------------------------------------------------------------
1920   | 21/07/2026 | Food            | Grocery Shopping          | $1250.50
```

---

### 3. View Total Spending Summary

Displays financial statistics based on the recorded expenses:

```text
==================================================
                FINANCIAL OVERVIEW
==================================================

  +----------------------------------------------+
  |  TOTAL SPENT :   2500.50                     |
  |  TOTAL ITEMS :   3                           |
  |  AVERAGE COST:   833.50/item                 |
  +----------------------------------------------+

  [!] Largest Expense :  1250.50 (Grocery Shopping)
  [*] Smallest Expense:  250.00 (Transport)
```

---

## Concepts Practiced

This project uses several important C programming concepts:

* Structures
* Nested structures
* Arrays of structures
* Functions
* Function prototypes
* `scanf()` input handling
* `fgets()` string input
* Input buffer cleanup
* String manipulation using `strcspn()`
* Loops
* Conditional statements
* `switch` statements
* Basic statistical calculations
* Formatted output using `printf()`

---

## Current Limitations

The current version stores all expenses in memory only.

This means:

* Data is lost when the program exits
* The maximum number of expenses is limited to 100
* Dates are not yet fully validated
* Categories cannot yet be filtered
* Expenses cannot yet be edited or deleted
* The program uses `float` for monetary values

---

## Future Improvements

Planned improvements include:

* [ ] Save expenses to a file
* [ ] Load expenses when the program starts
* [ ] Edit an existing expense
* [ ] Delete an expense
* [ ] Search expenses by description
* [ ] Filter expenses by category
* [ ] Filter expenses by date
* [ ] Sort expenses by amount or date
* [ ] Generate category-wise spending summaries
* [ ] Add proper date validation
* [ ] Refactor the project into multiple `.c` and `.h` files
* [ ] Add a build system such as a `Makefile`

---

## Learning Goal

This project is part of my journey to improve my **C programming and software development skills** by building practical command-line applications.

The goal is not only to make the program work, but also to gradually improve:

* Code organization
* Input validation
* Error handling
* Data management
* File handling
* Modular programming
* Software project structure

---

## Author

**Ayush Jain**

---

## License

This project is open-source and available for learning and educational purposes.
