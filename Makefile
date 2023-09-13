# Compiler settings
CC = gcc
CFLAGS = -Wall -std=c11

# Directories
SRC_DIR = src
TEST_DIR = test

# Targets
test: $(TEST_DIR)/test.c $(SRC_DIR)/monad.h
	$(CC) $(CFLAGS) $(TEST_DIR)/test.c -o $(TEST_DIR)/test
	./$(TEST_DIR)/test

clean:
	rm -f main $(TEST_DIR)/test
