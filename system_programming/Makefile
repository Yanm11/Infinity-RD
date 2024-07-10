# Directories
SRC_DIR = ./src
TEST_DIR = ./test
BIN_DIR_DEBUG = ./bin/debug
BIN_DIR_RELEASE = ./bin/release
INCLUDE_DIR = ./include

# Compiler and flags
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(INCLUDE_DIR)/
DEBUGFLAGS = -g
RELEASEFLAGS = -DNDEBUG -O3
LIBFLAGS = -shared -fPIC -lm

# Automatically find all source and test files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*_test.c)

# Create lists of object files and executables
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC_FILES))
TEST_OBJS = $(patsubst $(TEST_DIR)/%_test.c, $(TEST_DIR)/%_test.o, $(TEST_FILES))
DEBUG_EXES = $(patsubst $(TEST_DIR)/%_test.c, $(BIN_DIR_DEBUG)/%, $(TEST_FILES))
RELEASE_EXES = $(patsubst $(TEST_DIR)/%_test.c, $(BIN_DIR_RELEASE)/%, $(TEST_FILES))

.SECONDARY: $(SRC_OBJS) $(TEST_OBJS)
.PRECIOUS: $(SRC_OBJS) $(TEST_OBJS)

# Default target
.PHONY: all
all: debug release

# Debug build
.PHONY: debug
debug: $(INCLUDE_DIR)/libmydslib_debug.so

$(INCLUDE_DIR)/libmydslib_debug.so: $(SRC_OBJS)
	@echo "Creating the debug shared library libmydslib_debug.so..."
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) $(LIBFLAGS) -o $@ $^

# Release build
.PHONY: release
release: $(INCLUDE_DIR)/libmydslib_release.so

$(INCLUDE_DIR)/libmydslib_release.so: $(SRC_OBJS)
	@echo "Creating the release shared library libmydslib_release.so..."
	@$(CC) $(CFLAGS) $(RELEASEFLAGS) $(LIBFLAGS) -o $@ $^

# Compile source files to object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	@echo "Compiling and assembling $(basename $(notdir $<))..."
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

# Compile test files to object files
$(TEST_DIR)/%_test.o: $(TEST_DIR)/%_test.c $(INCLUDE_DIR)/%.h
	@echo "Compiling and assembling $(basename $(notdir $<))..."
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

# Link object files to create debug executables
$(BIN_DIR_DEBUG)/%: $(TEST_DIR)/%_test.o $(INCLUDE_DIR)/libmydslib_debug.so | $(BIN_DIR_DEBUG)
	@echo "Linking $(basename $(notdir $@)) for debug..."
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $< -L$(INCLUDE_DIR) -lmydslib_debug -lm

# Link object files to create release executables
$(BIN_DIR_RELEASE)/%: $(TEST_DIR)/%_test.o $(INCLUDE_DIR)/libmydslib_release.so | $(BIN_DIR_RELEASE)
	@echo "Linking $(basename $(notdir $@)) for release..."
	@$(CC) $(CFLAGS) $(RELEASEFLAGS) -o $@ $< -L$(INCLUDE_DIR) -lmydslib_release

# Build all test executables using the debug shared library
.PHONY: test
test: $(DEBUG_EXES)

# Clean up build files
.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(BIN_DIR_DEBUG)/* $(INCLUDE_DIR)/libmydslib_debug.so $(INCLUDE_DIR)/libmydslib_release.so
