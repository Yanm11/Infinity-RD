# flags and compiler
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
CC = gcc

# file names
FILE_SRC = stack
#FILE_SRC2 = sllist
FILE_ICLUDE = stack.h
# FILE_ICLUDE2 = sllist.h
FILE_TEST = quiz14
FILE_OUT = quiz14


# dir locations
SRC_DIR = ~/git/ds/src
TEST_DIR = .
BIN_DIR = .
INCLUDE_DIR = ~/git/ds/include

# objects
objects = $(TEST_DIR)/$(FILE_TEST).o $(SRC_DIR)/$(FILE_SRC).o
# $(FILE_SRC2).o 

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

# $(FILE_SRC2).o : $(FILE_SRC2).c $(INCLUDE_DIR)/$(FILE_ICLUDE2)
#	$(CC) $(CFLAGS) -c $(FILE_SRC2).c -I $(INCLUDE_DIR)


libfoo.a: $(libobjects)
	ar rcs libfoo.a $(libobjects)
    
.PHONY : clean
clean :
	rm $(BIN_DIR)/$(FILE_OUT) ../bin/release//$(FILE_OUT)  $(objects) libfoo.a
