# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread


$(BIN_DIR)/LListGTest: test.cpp $(BIN_DIR)/llistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

.PHONY: tests clean

tests: $(BIN_DIR)/LListGTest
	-@$(BIN_DIR)/LListGTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)/LListGTest
	-@echo "--- All Clean!---"
