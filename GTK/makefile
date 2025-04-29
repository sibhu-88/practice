# Compiler and Flags
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -g
LIBS = `pkg-config --libs gtk+-3.0 gdk-pixbuf-2.0`

# Executable Name
EXECUTABLE = myapp

# Source Files
SOURCE = main.c

# Object Files
OBJECTS = $(SOURCE:.c=.o)

# Rule to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LIBS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
