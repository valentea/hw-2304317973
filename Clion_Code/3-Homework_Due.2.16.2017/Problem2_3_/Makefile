BIN_DIR = bin
CXX = g++
CPPFLAGS = -Wall -g


all: llistint_test
	

llistint_test: llistint.o
	$(CXX) -g -Wall llistint.o llistdbl_test.cpp -o llistint_test
    

llistint.o: llistint.h llistint.cpp
	$(CXX) -g -Wall -c llistint.cpp -o llistint.o
	

	
.PHONY: clean
clean:
	rm -f llistint.o
