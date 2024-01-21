CC = gcc
CFLAGS = -std=c++17 -Wall -pedantic -Wextra -I3DViewer/model
UNITFLAGS1 := $(shell pkg-config --cflags gtest)
UNITFLAGS2 := $(shell pkg-config --libs gtest)

UNITOBJS = ./out/tests.o
OBJS = ./out/edges.o ./out/faces.o ./out/figure.o ./out/point.o ./out/points.o
GCOV_FLAGS =

.PHONY: all clean fclean test install uninstall dvi dist gcov_report style_change style_check

all: clean install\

OS := $(shell uname)
ifeq ($(OS), Darwin)
    QMK = qmake
    3DV = 3DViewer.app
	TEST_FLAGS = -DGTEST_HAS_PTHREAD=1 -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main
else
    QMK = qmake6
    3DV = 3DViewer
	TEST_FLAGS = -lgtest -lm

endif



install:
	@echo "Start installation"
	@mkdir -p build
	@cd 3DViewer && $(QMK) > /dev/null && make > /dev/null && rm -rf Makefile && rm -rf ../build/$(3DV) && mv $(3DV) ../build/$(3DV)
	@cp -R build/$(3DV) ~/Desktop/$(3DV)
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃    build folder and on the desktop.     ┃"
	@echo "┗=========================================┛"

uninstall:
	@rm -rf ~/Desktop/$(3DV)
	@rm -rf build/$(3DV)
	@echo "┏==================================┓"
	@echo "┃ Uninstall completed successfully ┃"
	@echo "┗==================================┛"

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p dist
	@cp -R build/$(3DV) dist
	@cp ../README_RUS.md dist && cp ../README.md dist
	@cd dist && tar cvzf 3DViewer.tgz *
	@cd dist && rm -rf $(3DV) README.md README_RUS.md
	@echo "The build was successfully archived"

tests : $(OBJS) $(UNITOBJS)
	$(CC) -o tests $(UNITOBJS) $(OBJS) $(TEST_FLAGS) -lstdc++ -fprofile-arcs -ftest-coverage
	./tests

./out/%.o : ./3DViewer/model/%.cc
	mkdir -p ./out
	$(CC) $(CFLAGS) $(UNITFLAGS1) $(COV_FLAG) -c $<
	mv ./*.o ./out/

./out/tests.o : ./test/tests.cc
	mkdir -p ./out
	$(CC) $(CFLAGS) -c $< $(UNITFLAGS1)
	mv ./*.o ./out/

coverage:
	@./test
	@echo "┏==================================┓"
	@echo "┃  Testing completed successfully  ┃"
	@echo "┗==================================┛"

gcov_report: GCOV_FLAGS += --coverage
gcov_report: clean test
	@echo "┏=========================================┓"
	@echo "┃     Generating your html report ...     ┃"
	@echo "┗=========================================┛"
	@lcov -t test -o test.info -c -d . --exclude '*/tests/*' --ignore-errors source
	@genhtml --ignore-errors unmapped -o test_html test.info
	@rm -rf *.gc* tests/*.gc*
	@rm -rf *.gd* tests/*.gd*
	@open ./test_html/index.html

style_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -n 3DViewer/*/*.cc 3DViewer/*/*.h 3DViewer/*.cc 3DViewer/*.h test/*.cc
	@rm ./.clang-format

style_change:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -i 3DViewer/*/*.cc 3DViewer/*/*.h 3DViewer/*.cc 3DViewer/*.h test/*.cc
	@rm ./.clang-format

clean:
	@rm -rf test/testing *.gcno *.gcov 3DViewer/*.o *.gcda *.info gcov_report
	@rm -rf 3DViewer/.qmake.stash 3DViewer/*.user 3DViewer/moc_*
	@rm -rf test/*.gcno test/*.o test/*gcda
	@rm -rf tests test.gcda test.gcno 
	@rm -rf out


fclean: clean
	@rm -rf dist ~/Desktop/$(3DV) build* test_html

