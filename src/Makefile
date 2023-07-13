CC=gcc
CFLAGS=-c -Wall -Wextra -Werror
LC=lcov -c -d . -o
AFLAGS=ar rc
GCOVFLAGS=--coverage
SOURCES=$(wildcard *.c)
TESTS=$(wildcard ./*tests.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))
TESTOBJ=$(patsubst %.c, %.o, $(TESTS))
LIBOBJ=$(patsubst %.c, %.o, s21_matrix.c)
OFLAGS=-lcheck -lm -lpthread -lgcov -o

all: s21_matrix.a s21_matrix.o test style_check gcov_report 

# компилим бибдлиотеку

%.o: %.c
	$(CC) $(CFLAGS) $< $(GCOVFLAGS) -o $@

s21_matrix.a:
	$(CC) $(CFLAGS) s21_matrix.c
	$(AFLAGS) s21_matrix.a $(LIBOBJ)
	rm -rf *.o

# компилим тесты

s21_%_tests.o: $(TESTS)
	$(CC) $(CFLAGS) $< $(GCOVFLAGS) -o $@

test: 
	gcc -o test --coverage *.c -lcheck -lpthread -lm  -I /usr/local/include -L/usr/local/lib
	./test

# компилим покрытие

gcov_report:
	$(LC) report.info
	genhtml -o rrr report.info
	cd ./rrr; open index.html

# доп функции

style_check:
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.html *.css *.png *.out.dSYM main.c *.out *.gch
	rm -rf ./tests/*.o ./tests/*.gcda ./tests/*.gcno
	rm -rf test src
	rm -r rrr

retest: clean test

rebuild: clean all

build: all

git:
	git add .
	git commit -m 'done with leaks'
	git push origin develop

val: test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test