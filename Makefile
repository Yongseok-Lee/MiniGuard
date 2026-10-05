CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude
SOURCES = src/main.c src/config.c src/watcher.c
HEADERS = include/config.h include/watcher.h
TARGET = miniguard

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
