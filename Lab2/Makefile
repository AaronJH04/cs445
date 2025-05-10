CC = gcc
CFLAGS = -Wall -Wextra
TARGET = process_manager

all: $(TARGET)

$(TARGET): process_manager.c
	$(CC) $(CFLAGS) -o $(TARGET) process_manager.c

clean:
	rm -f $(TARGET)
