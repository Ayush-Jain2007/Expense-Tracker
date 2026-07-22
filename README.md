# Personal Expense Tracker

A console-based personal expense tracker written in **C**. This project allows users to record, view, manage, and analyze their daily expenses through a simple terminal interface.

The project is being developed incrementally to practice core C programming concepts such as structures, arrays, functions, file handling, input validation, modular programming, and project organization.

---

## Current Version

**Version 1.5 — Delete Expense by ID**

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
* Delete an expense by ID
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
* Save expenses to a binary file
* Load previously saved expenses when the program starts
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
├── expense.c
├── expense.h
├── file.c
├── file.h
├── .gitignore
├── README.md
│
├── expenses.dat      # Generated locally, ignored by Git
└── output/           # Build output, ignored by Git
```

### File Responsibilities

#### `main.c`

Contains:

* Main menu
* User input for menu choices
* Program flow

#### `expense.c`

Contains:

* Expense data
* Expense creation
* Expense display
* Expense lookup
* Expense deletion
* Date validation
* Spending summary

#### `expense.h`

Contains:

* `Date` structure
* `Expense` structure
* Shared constants
* Global variable declarations
* Expense function prototypes

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

When an expense is added or deleted, the updated expense data is saved automatically.

```text
Program starts
      ↓
Load expenses.dat
      ↓
Use application
      ↓
Add or delete expense
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
gcc -Wall -Wextra -g main.c expense.c file.c -o output/expense_tracker
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
  [4] Delete Expense By ID
  [5] View Total Spending Summary
  [6] Exit Application
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
ID doesn't exist!
```

The lookup is implemented using:

```c
int findExpenseById(int id);
```

This function searches the expense array and returns the matching array index.

---

### 4. Delete Expense By ID

Allows the user to delete a specific expense using its ID.

```text
Enter ID: 1920
Expense deleted successfully!
```

When an expense is deleted, the remaining expenses are shifted left in the array:

```text
Before:
[Expense A] [Expense B] [Expense C] [Expense D]

Delete Expense B:

After:
[Expense A] [Expense C] [Expense D]
```

The updated expense list is then saved to `expenses.dat`.

---

### 5. View Total Spending Summary

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

### Version 1.5 — Delete Expense by ID

* Delete an expense using its ID
* Reuse `findExpenseById()` to locate expenses
* Shift remaining expenses after deletion
* Decrease the total expense count
* Save the updated expense data to the binary file
* Handle non-existent expense IDs

---

## Current Limitations

* Maximum of 100 expenses
* Expenses are stored in a binary file
* No edit functionality
* No search by description
* No category filtering
* No date filtering
* No sorting functionality
* The program uses `float` for monetary values
* Input handling can be further improved

---

## Future Improvements

* [x] Save expenses to a file
* [x] Load expenses when the program starts
* [x] Add proper date validation
* [x] Refactor the project into multiple `.c` and `.h` files
* [x] Search for an expense by ID
* [x] Delete an expense by ID
* [ ] Edit an existing expense
* [ ] Search expenses by description
* [ ] Filter expenses by category
* [ ] Filter expenses by date
* [ ] Sort expenses by amount or date
* [ ] Generate category-wise spending summaries
* [ ] Add a build system such as a `Makefile`
* [ ] Replace fixed-size storage with dynamic memory
* [ ] Improve monetary value handling using integer cents instead of `float`

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
