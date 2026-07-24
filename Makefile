CC = gcc
CFLAGS = -Wall -Wextra -g3

TARGET = output/expense_tracker.exe

SRC = main.c expense.c file.c utils.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	$(TARGET)

clean:
	del /Q "$(TARGET)"