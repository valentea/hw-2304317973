# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread


$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

$(BIN_DIR)/LListGTest: test.cpp $(BIN_DIR)/llistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@
	
$(BIN_DIR)/llistint.o: $(BIN_DIR)/.dirstamp llistint.cpp llistint.h
	$(CXX) $(CPPFLAGS) -c llistint.cpp -o $(BIN_DIR)/llistint.o

.PHONY: clean listtest

listtest: $(BIN_DIR)/LListGTest
	-@$(BIN_DIR)/LListGTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
