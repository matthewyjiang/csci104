# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
arrayTest: test.cpp arraylist.o
	$(CC) $(CPPFLAGS) test.cpp -no-pie arraylist.o $(GTEST_LL) -o arrayTest

.PHONY: tests clean

tests: arrayTest
	-@./arrayTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf arrayTest
	-@echo "--- All Clean!---"