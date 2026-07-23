# Personal Expense Tracker

A console-based personal expense tracker written in **C**. This project allows users to record, view, edit, delete, filter, and analyze their daily expenses through a simple terminal interface.

The project is being developed incrementally to practice core C programming concepts such as structures, arrays, functions, file handling, input validation, modular programming, and project organization.

---

## Current Version

**Version 1.6 — Expense Sorting**

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
* Save expenses to a binary file
* Load previously saved expenses when the program starts
* Supports up to **100 expenses**

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
├── expenses.dat
├── output/
└── README.md
````

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
* Shared constants
* Global variable declarations
* Function prototypes

#### `file.c`

Contains:

* Saving expenses
* Loading expenses
* Binary file handling

#### `file.h`

Contains:

* File function prototypes

---

## Data Structures

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
gcc main.c expense.c file.c -o output/expense_tracker
```

For additional compiler warnings:

```bash
gcc -Wall -Wextra -g3 main.c expense.c file.c -o output/expense_tracker
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
  [8] View Total Spending Summary
  [9] Exit Application
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
* Nested structures
* Arrays of structures
* Functions
* Function prototypes
* Header files
* Header guards
* Multiple source files
* `extern` variables
* `scanf()` input handling
* `fgets()` string input
* Input buffer cleanup
* String manipulation using `strcspn()`
* `strcmp()` string comparison
* Loops
* Conditional statements
* `switch` statements
* File handling
* Binary file I/O
* `fopen()`
* `fclose()`
* `fread()`
* `fwrite()`
* Input validation
* Leap year calculations
* Array searching
* Array element shifting
* Filtering data
* Basic statistical calculations
* Formatted output using `printf()`

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

### Version 1.5 — Expense Filtering

* Filter expenses by category
* Filter expenses by month and year
* Display matching expenses
* Display the number of matching expenses

### Version 1.6 — Expense Sorting

* Sort expenses by amount
* Sort expenses by date
* Support ascending sorting
* Support descending sorting
* Save the sorted order to the binary data file

---

## Current Limitations

* Maximum of 100 expenses
* Expenses are stored in a binary file
* No search by description
* No sorting functionality
* No category-wise spending summary
* The program uses `float` for monetary values
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
* [ ] Generate category-wise spending summaries
* [ ] Add a build system such as a `Makefile`
* [ ] Replace fixed-size storage with dynamic memory
* [ ] Improve monetary value handling using integer cents instead of `float`
* [ ] Create reusable input utility functions
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