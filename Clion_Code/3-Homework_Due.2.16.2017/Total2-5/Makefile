# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all:llistint1 queueList1 scheduling1

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

llistint1: $(BIN_DIR)/.dirstamp $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) llistint_test.cpp $(BIN_DIR)/llistint.o -o llistint

queueList1: $(BIN_DIR)/.dirstamp $(BIN_DIR)/queueint.o
	$(CXX) $(CPPFLAGS) QueueList.cpp $(BIN_DIR)/queueint.o $(BIN_DIR)/llistint.o -o queueList
	
scheduling1: $(BIN_DIR)/.dirstamp $(BIN_DIR)/queueint.o
	$(CXX) $(CPPFLAGS) scheduling.cpp $(BIN_DIR)/queueint.o $(BIN_DIR)/llistint.o -o scheduling

LListGTest1: test.cpp $(BIN_DIR)/llistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@
	
$(BIN_DIR)/llistint.o: $(BIN_DIR)/.dirstamp llistint.cpp llistint.h
	$(CXX) $(CPPFLAGS) -c llistint.cpp -o $(BIN_DIR)/llistint.o
	
$(BIN_DIR)/queueint.o: $(BIN_DIR)/.dirstamp queueint.cpp queueint.h
	$(CXX) $(CPPFLAGS) -c $(BIN_DIR)/queueint.o -o queueint.cpp 




.PHONY: clean llistGtest llistint queueList scheduling

llistint:
	./llistint
	
queueList:
	./queueList
	
scheduling:
	./scheduling workload1.in

llistGtest: $(BIN_DIR)/LListGTest
	-@$(BIN_DIR)/LListGTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"

