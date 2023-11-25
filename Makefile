# Define compiler
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -Iinclude -lm

# Define the directory for the object files
ODIR = src

# Define your source files
SRC = $(ODIR)/main.c $(ODIR)/Graphic.c $(ODIR)/GraphTools.c $(ODIR)/ListTools.c

# Define the target executable
TARGET = $(ODIR)/main

$(TARGET): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run

# Target to run the program
run: $(TARGET)
	cd $(ODIR) && ./main

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
