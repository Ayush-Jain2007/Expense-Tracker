# Personal Expense Tracker

A console-based personal expense tracker written in **C**. This project allows users to record, view, edit, delete, filter, and analyze their daily expenses through a simple terminal interface.

The project is being developed incrementally to practice core C programming concepts such as structures, arrays, functions, file handling, input validation, modular programming, and project organization.

---

## Current Version

**Version 2.2 — Integer-Based Monetary Value Handling**

---

## Features

* Add new expenses
* Automatically generate expense IDs
* Store:
  * Expense description
  * Expense category
  * Amount
  * Date
* View all recorded expenses in a formatted table
* Search for an expense by ID
* Display a single expense by ID
* Edit existing expenses
* Delete expenses by ID
* Filter expenses by category
* Filter expenses by month and year
* Calculate a spending summary
* Display:
  * Total amount spent
  * Total number of expenses
  * Average expense amount
  * Largest expense
  * Smallest expense
* Validate numeric input
* Validate expense amounts
* Validate dates, including leap years
* Sort expenses by amount
* Sort expenses by date
* Sort in ascending or descending order
* Generate category-wise spending summaries
* Display the number of expenses in each category
* Display the total amount spent per category
* Save expenses to a binary file
* Reusable input validation utilities
* Safe integer input handling
* Integer range validation
* Safe floating-point input handling
* Centralized input buffer cleanup
* Encapsulate expense data inside an `ExpenseManager` structure
* Pass expense data between modules using structure pointers
* Reduce reliance on global variables
* Load previously saved expenses when the program starts
* Supports up to **100 expenses**
* Reusable expense display functions
* Centralized expense table formatting
* Reusable screen pause utility
* Reduced duplicated display logic
* Store monetary values as integer cents
* Avoid floating-point precision issues for monetary calculations
* Display monetary values with proper decimal formatting

---

## Technologies Used

* **Language:** C
* **Standard:** C99
* **Compiler:** GCC
* **Libraries:**
  * `stdio.h`
  * `string.h`

---

## Project Structure

```text
expense-tracker/
│
├── main.c
├── expense.c
├── expense.h
├── file.c
├── file.h
├── utils.c
├── utils.h
├── expenses.dat
├── output/
└── README.md
```

> `expenses.dat` and the `output/` directory are generated locally and are ignored by Git.

### File Responsibilities

#### `main.c`

Contains:

* Main menu
* Filter submenu
* User input for menu choices
* Program flow

#### `expense.c`

Contains:

* Reusable expense display formatting
* Expense table header formatting
* Expense table separator formatting
* Expense data
* Expense creation
* Expense display
* Expense lookup
* Expense editing
* Expense deletion
* Category filtering
* Date filtering
* Date validation
* Spending summary

#### `expense.h`

Contains:

* `Date` structure
* `Expense` structure
* `ExpenseManager` structure
* Shared constants
* Expense function prototypes

#### `file.c`

Contains:

* Saving expenses
* Loading expenses
* Binary file handling

#### `file.h`

Contains:

* File function prototypes

#### `utils.c`

Contains reusable utility functions for:

* Integer input handling
* Floating-point input handling
* String input handling
* Input buffer cleanup
* Screen pause functionality

#### `utils.h`

Contains prototypes for reusable utility functions.

---

## Data Structures

Each expense is represented using a `struct Expense`.

```c
struct Expense
{
    int id;
    char description[50];
    char category[50];
    long amount;
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

## ExpenseManager Architecture

Starting with Version 2.0, expense data is encapsulated inside an
`ExpenseManager` structure:

```c
struct ExpenseManager
{
    struct Expense expenses[MAX_EXPENSES];
    int count;
};
```

---

## File Persistence

Expenses are stored in a binary file named:

```text
expenses.dat
```

When the program starts, previously saved expenses are loaded from the file.

When an expense is added, edited, or deleted, the updated expense data is saved automatically.

```text
Program starts
      ↓
Load expenses.dat
      ↓
Use application
      ↓
Add / Edit / Delete expense
      ↓
Save expenses.dat
```

This allows expense data to persist between program executions.

---

## How to Compile

Using GCC:

```bash
gcc main.c expense.c file.c utils.c -o output/expense_tracker
```

For additional compiler warnings:

```bash
gcc -Wall -Wextra -g3 main.c expense.c file.c utils.c -o output/expense_tracker
```

---

## How to Run

### Windows

```powershell
.\output\expense_tracker.exe
```

### Linux / macOS

```bash
./output/expense_tracker
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
  [3] View Expense By ID
  [4] Edit Expense
  [5] Delete Expense
  [6] Filter Expense
  [7] Sort Expenses
  [8] Category Summary
  [9] View Total Spending Summary
  [10] Exit Application
```

---

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

The expense is validated and then saved to `expenses.dat`.

---

### 2. View All Expenses

Displays all recorded expenses in a formatted table:

```text
ID     | Date       | Category        | Description               | Amount ($)
-------------------------------------------------------------------------------
1920   | 21/07/2026 | Food            | Grocery Shopping          | $1250.50
```

---

### 3. View Expense By ID

Allows the user to search for a specific expense using its unique ID.

```text
Enter ID: 1920
```

The matching expense is then displayed.

If the ID does not exist:

```text
Expense with ID 1920 not found!
```

The lookup is implemented using:

```c
int findExpenseById(int id);
```

This function searches the expense array and returns the matching array index.

---

### 4. Edit Expense

Allows the user to modify an existing expense using its ID.

The following fields can be updated:

* Description
* Category
* Amount
* Day
* Month
* Year

Example:

```text
Enter ID to edit: 1920
Enter new Description: Monthly Grocery Shopping
Enter new Category: Food
Enter new Amount: 1500.00
Enter Day: 21
Enter Month: 7
Enter Year: 2026
```

The updated expense is validated and saved to the binary file.

The expense ID remains unchanged.

---

### 5. Delete Expense

Allows the user to delete an expense using its ID.

Example:

```text
Enter ID: 1920
```

When an expense is deleted, the remaining expenses are shifted in the array to fill the empty position.

The updated data is then saved to `expenses.dat`.

---

### 6. Filter Expenses

The program provides filtering options:

```text
===============================================================================
                                FILTER EXPENSE
===============================================================================

  [1] Filter Expense By Category
  [2] Filter Expense By Date
  [3] Return

-------------------------------------------------------------------------------
```

#### Filter by Category

The user can enter a category and view all matching expenses.

Example:

```text
Enter Category: Food
```

The program displays all expenses belonging to the `Food` category.

#### Filter by Date

Expenses can be filtered by month and year.

Example:

```text
Enter Month: 7
Enter Year: 2026
```

The program displays all expenses recorded during July 2026.

If no matching expenses are found, the program displays an appropriate message.

---

### 7. View Total Spending Summary

Displays financial statistics based on the recorded expenses:

```text
==================================================
                FINANCIAL OVERVIEW
==================================================

  +----------------------------------------------+
  |  TOTAL SPENT :  2500.50                      |
  |  TOTAL ITEMS :     3                         |
  |  AVERAGE COST:   833.50/item                 |
  +----------------------------------------------+

  [!] Largest Expense :  1250.50 (Grocery Shopping)
  [*] Smallest Expense:  250.00 (Transport)
```

---

## Input Validation

The program validates:

### Expense Amount

* Must be a valid number.
* Must be greater than `0`.

### Day

* Must be between `1` and `31`.
* Must be valid for the selected month.

### Month

* Must be between `1` and `12`.

### Year

* Must be between `1` and `3000`.

### Leap Years

The program correctly handles leap years.

For example:

```text
29/02/2024 → Valid
29/02/2025 → Invalid
```

---

## Concepts Practiced

This project uses several important C programming concepts:

* Structures
* Arrays
* Functions
* Multiple source files
* Header files
* File I/O
* Input validation
* Searching
* Editing
* Deleting
* Filtering
* Sorting
* Code reuse
* Utility modules
* Centralized input validation
* Abstraction
* Defensive input handling
* Structure pointers
* Passing structures to functions
* Passing structures by address
* Pointer member access using `->`
* Data encapsulation
* Reducing global state
* Manager-style data architecture
* Data aggregation
* Code refactoring
* Code reuse
* Separation of concerns
* Reducing code duplication
* Helper functions
* Modular display logic
* Integer-based monetary representation
* Avoiding floating-point precision issues
* Data representation
* Integer division and remainder operations

---

## Version History

### Version 1.0 — Basic Expense Tracker

* Add expenses
* View all expenses
* Calculate spending summary
* Store expense information using structures

### Version 1.1 — Improved Reliability

* Validate expense amounts
* Reject zero and negative amounts
* Validate day, month, and year ranges
* Add comprehensive date validation
* Add leap year support

### Version 1.2 — File Persistence

* Save expenses to a binary file
* Load expenses when the program starts
* Preserve expense data between program executions
* Validate loaded expense count

### Version 1.3 — Modular Project Structure

* Split the program into multiple source files
* Create separate header files
* Separate expense logic from file handling
* Use `extern` for shared global variables
* Add header guards

### Version 1.4 — Expense Lookup by ID

* Search for an expense by ID
* Display a single expense
* Handle non-existent expense IDs
* Create reusable `findExpenseById()` function

### * Version 1.5 — Expense Management

* Edit an existing expense by ID
* Delete an expense by ID
* Reuse `findExpenseById()`
* Save changes to the binary file
* Maintain array integrity after deletion

### Version 1.6 — Expense Filtering

* Filter expenses by category
* Filter expenses by month and year
* Display matching expenses
* Display the number of matching expenses

### Version 1.7 — Expense Sorting

* Sort expenses by amount
* Sort expenses by date
* Support ascending sorting
* Support descending sorting
* Save the sorted order to the binary data file

### Version 1.8 — Category-wise Spending Summary

* Group expenses by category
* Count expenses in each category
* Calculate total spending per category
* Display category-wise financial statistics

### Version 1.9 — Reusable Input Handling Utilities

* Create reusable `getInt()` function
* Create reusable `getIntInRange()` function
* Create reusable `getFloat()` function
* Centralize input buffer cleanup
* Reduce duplicated input validation code
* Improve input handling throughout the application

### Version 2.0 — ExpenseManager Architecture

* Introduced `struct ExpenseManager`
* Encapsulated the expense array and expense count
* Removed direct global access to expense data
* Updated functions to receive an `ExpenseManager` pointer
* Improved data flow between modules
* Updated file persistence functions to work with the manager
* Updated CRUD, filtering, sorting, and summary operations

### Version 2.1 — Display Logic Refactoring

* Added reusable `displayExpense()` function
* Added reusable `displayExpenseTableHeader()` function
* Added reusable `displayExpenseTableLine()` function
* Added reusable `pauseScreen()` utility
* Reduced duplicated expense display code
* Improved code organization and maintainability

### Version 2.2 — Integer-Based Monetary Value Handling

* Replaced `float` monetary values with integer cents
* Updated expense amount storage to use `long`
* Updated expense input conversion
* Updated expense display formatting
* Updated spending summary calculations
* Updated category summary calculations
* Preserved sorting functionality with integer monetary values
* Improved monetary calculation reliability

---

## Current Limitations

* Maximum of 100 expenses
* Expenses are stored in a binary file
* Input handling can be further improved
* Some input logic is repeated across multiple functions

---

## Future Improvements

* [x] Save expenses to a file
* [x] Load expenses when the program starts
* [x] Add proper date validation
* [x] Refactor the project into multiple `.c` and `.h` files
* [x] Search for an expense by ID
* [x] Edit an existing expense
* [x] Delete an expense
* [x] Filter expenses by category
* [x] Filter expenses by date
* [x] Sort expenses by amount or date
* [x] Generate category-wise spending summaries
* [x] Create reusable input handling utilities
* [x] Improve monetary value handling using integer cents instead of `float`
* [ ] Add a build system such as a `Makefile`
* [ ] Replace fixed-size storage with dynamic memory
* [ ] Improve error handling for file operations

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

The project is being developed incrementally, with each version introducing new concepts and improving the quality of the application.

---

## Author

**Ayush Jain**

---

## License

This project is open-source and available for learning and educational purposes.

```

One small note: your README now correctly describes the project as **v1.6**, but the next feature should probably be **searching expenses by description** or **refactoring repeated input handling into utility functions**.
```