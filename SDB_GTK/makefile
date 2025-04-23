# Compiler and Flags
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -g
LIBS = `pkg-config --libs gtk+-3.0`

# Executable Name
EXECUTABLE = studentdb

# Source Files
SOURCE = main.c menu.c add_record.c add_data.c list_record.c modify_record.c sort_record.c save_record.c

# Object Files
OBJECTS = $(SOURCE:.c=.o)

# Rule to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LIBS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
