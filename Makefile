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

.PHONY: clean run test

# Target to run the program
run: $(TARGET)
	cd $(ODIR) && ./main

# Target to compile and run the tests
test:
	$(CC) -o $(ODIR)/test $(filter-out $(ODIR)/main.c, $(SRC)) $(ODIR)/Tests.c $(CFLAGS)
	cd $(ODIR) && ./test

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(ODIR)/test
