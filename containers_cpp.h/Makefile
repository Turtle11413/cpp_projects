CC=gcc
CPPFLAGS=-Wall -Werror -Wextra -std=c++17 -lstdc++

OBJ_MAIN=tests/test_main.cc
OBJ_MAP=tests/test_map.cc
OBJ_SET=tests/test_set.cc
OBJ_VECTOR=tests/test_vector.cc
OBJ_ARRAY=tests/test_array.cc
OBJ_MULTISET=tests/test_multiset.cc
OBJ_TEST=$(OBJ_SET) $(OBJ_VECTOR) $(OBJ_ARRAY) $(OBJ_MULTISET) $(OBJ_MAIN) $(OBJ_MAP)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	LEAKS_CMD = valgrind --tool=memcheck --leak-check=yes
	ADD_LIB = -lgtest -lpthread -lm -lstdc++
	GCOV_FLAGS =
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open -a "Google Chrome"
	LEAKS_CMD = leaks -atExit --
	ADD_LIB = -lgtest -lm
	GCOV_FLAGS = --ignore-errors mismatch
endif

all: test

test: clean
	@$(CC) $(CPPFLAGS) $(OBJ_TEST) -o test $(ADD_LIB)
	@$(LEAKS_CMD) ./test

gcov: clean
	@$(CC) $(CPPFLAGS) --coverage $(OBJ_TEST) -o test $(ADD_LIB)
	@./test
	@rm -rf test_main.gcda test_main.gcno
	@lcov -t "s21_containers_test" -o fizzbuzz.info -c -d . $(GCOV_FLAGS)
	@genhtml -o report fizzbuzz.info
	@$(OPEN_CMD) report/index.html

style:
	@clang-format -style=Google -i *.h */*.h */*.tpp */*.cc

clean:
	@-rm -rf *.o *.gcno *.gcda *.info *.gcov *.a *.dSYM report test *.out
