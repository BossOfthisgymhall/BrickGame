TEST_FLAGS= -lgtest_main -pthread -lgtest
CXX= g++
FLAGS = -Wall -Wextra -Werror -std=c++17
GCO= --coverage
MODEL = brick_game/*.cc
VIEW = gui/*.cc
TERMINAL = gui/terminal/*.cc
FSM = controller/*.cc

SRC_DIR := .
EXTENSIONS := cc cpp h

UNAME := $(shell uname -s)

find_files = $(foreach ext,$(EXTENSIONS),$(wildcard $(1)/*.$(ext))) $(foreach d,$(wildcard $(1)/*),$(call find_files,$(d)))
SRC_FILES := $(call find_files,$(SRC_DIR))

CC_FILES := $(filter-out ./gui/desktop/main.cc ./gui/desktop/SnakeView.cc, $(filter %.cc,$(SRC_FILES)))

all: clean install test run_desktop

install: uninstall
	mkdir build
	cd build && cmake ../.. && make

run_desktop:
	cd build && ./desktop

run_terminal:
	cd build && ./terminal

uninstall:
	rm -rf build

test: clean
	$(CXX) $(FLAGS) -o test $(TEST_FLAGS) $(MODEL) $(FSM) test_snake/*.cc
	./test

gcov_report: clean
	$(CXX) $(FLAGS) $(TEST_FLAGS) $(GCO) test_snake/*.cc $(MODEL) $(FSM) -o report
	./report
	gcov *.gcno *.gcda
	lcov --capture --directory . --output-file coverage.info --no-external --ignore-errors inconsistent
	genhtml coverage.info --output-directory coverage_report
ifeq ($(UNAME), Linux)
	google-chrome ./coverage_report/index.html
else
	open ./coverage_report/index.html
endif
	rm -rf *.gcda *.gcno *.info  report *.gcov

dvi:
	open dvi.md

dist: install
	mkdir -p BrickGame
	cp -R build BrickGame/
	cp dvi.md BrickGame/
	tar cvzf BrickGame.tgz BrickGame/
	mv BrickGame.tgz ../
	rm -rf BrickGame/

clean:
	rm -rf build coverage_report
	rm -rf ./test
	clear
	make style

main: clean
	$(CXX) -o test $(TERMINAL) -lncurses

style:
	@cp ../materials/linters/.clang-format .
	clang-format -n $(SRC_FILES)
	clang-format -i $(SRC_FILES)
	@rm -rf .clang-format


