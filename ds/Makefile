# flags and compiler
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
CC = gcc

# file names
FILE_SRC = sortedlist
FILE_SRC2 = dllist
FILE_ICLUDE = sortedlist.h
FILE_ICLUDE2 = dllist.h
FILE_TEST = test_sortedlist
FILE_OUT = test_sortedlist


# dir locations
SRC_DIR = ./src
TEST_DIR = ./test
BIN_DIR = ./bin/debug
INCLUDE_DIR = ./include

# objects
objects = $(TEST_DIR)/$(FILE_TEST).o\
		  $(SRC_DIR)/$(FILE_SRC).o \
		  $(SRC_DIR)/$(FILE_SRC2).o 

libobjects = dvector.o


.PHONY : all
all: $(BIN_DIR)/$(FILE_OUT)

# Debug build
debug: CFLAGS += -g
debug: $(BIN_DIR)/$(FILE_OUT)

# Release build
release: CFLAGS += -DNDEBUG -O3
release: BIN_DIR = ../bin/release
release: $(BIN_DIR)/$(FILE_OUT)

$(BIN_DIR)/$(FILE_OUT) : $(objects)
	$(CC) -o $(BIN_DIR)/$(FILE_OUT) $(objects)

$(TEST_DIR)/$(FILE_TEST).o : $(TEST_DIR)/$(FILE_TEST).c $(INCLUDE_DIR)/$(FILE_ICLUDE) 
	$(CC) $(CFLAGS) -c $(TEST_DIR)/$(FILE_TEST).c -o $@ -I $(INCLUDE_DIR)

$(SRC_DIR)/$(FILE_SRC).o : $(SRC_DIR)/$(FILE_SRC).c $(INCLUDE_DIR)/$(FILE_ICLUDE)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(FILE_SRC).c -o $@ -I $(INCLUDE_DIR)

$(SRC_DIR)/$(FILE_SRC2).o : $(SRC_DIR)/$(FILE_SRC2).c $(INCLUDE_DIR)/$(FILE_ICLUDE2)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(FILE_SRC2).c $@ -I $(INCLUDE_DIR)


libfoo.a: $(libobjects)
	ar rcs libfoo.a $(libobjects)
    
.PHONY : clean
clean :
	rm $(BIN_DIR)/$(FILE_OUT) ../bin/release//$(FILE_OUT)  $(objects) libfoo.a
