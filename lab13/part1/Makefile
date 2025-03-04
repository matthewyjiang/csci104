# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: fibTest
	-@echo "--- All Built!---"

fib.o: fib.cpp fib.h
	$(CC) $(CPPFLAGS) -c fib.cpp -o fib.o

# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
fibTest: test.cpp fib.o
	$(CC) $(CPPFLAGS) test.cpp fib.o $(GTEST_LL) -o fibTest



.PHONY: clean tests

tests: fibTest
	-@./fibTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf fibTest fib.o
	-@echo "--- All Clean!---"
