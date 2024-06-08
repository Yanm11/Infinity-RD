# file names
FILE_SRC = scheduler
FILE_SRC2 = task
LIB = myscheduler
FILE_ICLUDE = scheduler.h
FILE_ICLUDE2 = task.h
FILE_TEST = test_scheduler
FILE_OUT = test_scheduler

# dir locations
SRC_DIR = ./src
TEST_DIR = ./test
BIN_DIR = ./bin/debug
INCLUDE_DIR = ./include

# flags and compiler
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(INCLUDE_DIR)
LDFLAGS = -L$(INCLUDE_DIR) -l$(LIB)
CC = gcc

# objects
objects = $(TEST_DIR)/$(FILE_TEST).o\
          $(SRC_DIR)/$(FILE_SRC).o \
          $(SRC_DIR)/$(FILE_SRC2).o

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
	$(CC) -o $(BIN_DIR)/$(FILE_OUT) $(objects) $(LDFLAGS)

$(TEST_DIR)/$(FILE_TEST).o : $(TEST_DIR)/$(FILE_TEST).c $(INCLUDE_DIR)/$(FILE_ICLUDE) 
	$(CC) $(CFLAGS) -c $(TEST_DIR)/$(FILE_TEST).c -o $@ 

$(SRC_DIR)/$(FILE_SRC).o : $(SRC_DIR)/$(FILE_SRC).c $(INCLUDE_DIR)/$(FILE_ICLUDE)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(FILE_SRC).c -o $@ 

$(SRC_DIR)/$(FILE_SRC2).o : $(SRC_DIR)/$(FILE_SRC2).c $(INCLUDE_DIR)/$(FILE_ICLUDE2)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(FILE_SRC2).c -o $@ 

.PHONY : clean
clean :
	rm -rf $(BIN_DIR)/$(FILE_OUT) $(objects)
