FLAGS = -Wall -Wextra -Werror -std=c11
CC = gcc
LFLAGS = -fprofile-arcs -ftest-coverage
SRC := $(wildcard funcs/*.c)
OBJ := $(patsubst funcs/*.c, %.o, $(SRC))
VALGRIND_FLAGS=--leak-check=full
VALGRIND_FLAGS_v2 = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med
LINUX_FLAGS=-lcheck -lsubunit -lm -lrt -lpthread
MAC_FLAGS=-lcheck -lm
OS := $(shell uname -s)


all: Mystring.a test gcov_report

gcov: gcov_report

test: Mystring.a
ifeq ($(OS),Linux)
	$(CC) $(FLAGS) $(OBJ) $(LFLAGS) check.c -o test $(LINUX_FLAGS)
	./test
endif
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) $(OBJ) $(LFLAGS) check.c -o test $(MAC_FLAGS)
	./test
endif

Mystring.a: 
	gcc -Wall -Wextra -Werror funcs/*.c -c
	ar rc libMystring.a *.o
	ranlib libMystring.a
	cp libMystring.a ./Mystring.a
	rm *.o

gcov_report: test
	gcov check.c
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory coverage-html
	rm -rf *.gcda *.gcno
ifeq ($(OS),Linux)
	xdg-open coverage-html/index.html

else
	open coverage-html/index.html
endif
	
stylemake:
	clang-format -style=Google -i Mystring.h check.c funcs/*.c

stylecheck:
	clang-format -style=Google -n Mystring.h check.c funcs/*.c

memory_check: Mystring.a
ifeq ($(OS),Linux)
	$(CC) $(FLAGS) check.c $< -o memory_test $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./memory_test
endif
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) check.c $< -o memory_test $(MAC_FLAGS)
	leaks --atExit -- ./memory_test      
endif

valgrind: test
	valgrind $(VALGRIND_FLAGS_v2) ./test
	grep -n "ERROR SUMMARY" valgrind.txt

clean:
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf *.gcda
	rm -rf *.a
	rm -rf *.info
	rm -rf *.a_check
	rm -rf gcov
	rm -rf coverage
	rm -rf coverage-html
	rm -rf test
	rm -rf memory_test
	rm -rf valgrind.txt