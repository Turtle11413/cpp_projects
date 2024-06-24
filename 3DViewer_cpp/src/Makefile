CC=gcc -std=c++17
CXXFLAGS=-Wall -Wextra -Werror -lstdc++
BUILD_DIR=build
OS:=$(shell uname -s)
ifeq ($(OS),Linux)
  OPEN_CMD=xdg-open
	LEAKS_CMD=valgrind --leak-check=full \
						--show-leak-kinds=all \
						--track-origins=yes \
						--verbose
	ADD_LIB=-lgtest -lgtest_main -lpthread -lm -lstdc++
	GCOV_FLAGS=
	APP_NAME=Viewer2
endif

ifeq ($(OS),Darwin)
	OPEN_CMD=open -a "Google Chrome"
	LEAKS_CMD=leaks -atExit --
	ADD_LIB=-lgtest -lgtest_main -lm
	GCOV_FLAGS=--ignore-errors mismatch
	APP_NAME=Viewer2.app
endif

all: install run_app

install: 
	@qmake -o qt.mk
	@make -f qt.mk all

uninstall: clean
	@rm -rf $(BUILD_DIR)

run_app: install
ifeq ($(OS),Darwin)
	./$(BUILD_DIR)/Viewer2.app/Contents/MacOS/Viewer2
endif
ifeq ($(OS),Linux)
	./$(BUILD_DIR)/Viewer2
endif

leaks: install
ifeq ($(OS),Darwin)
	@$(LEAKS_CMD) ./$(BUILD_DIR)/Viewer2.app/Contents/MacOS/Viewer2
endif
ifeq ($(OS),Linux)
	@$(LEAKS_CMD) ./$(BUILD_DIR)/Viewer2
endif

dvi:
	@$(OPEN_CMD) dvi.md

dist:
	@mkdir dist
	@cp -R viewer controller view test Makefile dvi.md Viewer2.pro shaders qtgifimage main.cc dist
	@cd dist && tar cvzf Viewer2_archive.tgz *
	@cd dist && rm -rf viewer/ controller/ view/ test/ Makefile dvi.md Viewer2.pro shaders/ qtgifimage/ main.cc

tests: clean
	@$(CC) $(CXXFLAGS) $(ADD_LIB) viewer/*.cc test/*.cc -o tests.out
	@$(LEAKS_CMD) ./tests.out

style:
	@clang-format -style=Google -i *.cc */*.h */*.cc

check_style:
	@clang-format -style=Google -n *.cc */*.h */*.cc

clean:
	@-rm -rf *.o *.gcno *.gcda *.info *.gcov *.a *.dSYM report *.out qt.mk build* moc* qrc*
