CC = g++
FLAGS = -Wall -Wextra -Werror
GCOV = -coverage
GTEST_LIB = -lgtest -lgmock -pthread



all : clean build run_test1 run_test2 run_test3 run_test4 run_test5 run_test6 run_test7

build:
	$(CC) $(FLAGS) -g bmp_reader.cpp main.cpp -o bmp_reader

run_test1:
	./bmp_reader /home/dorothyz/project/c++/BMP-reader/materials/test_img/test1.bmp

run_test2:
	./bmp_reader /home/dorothyz/project/c++/BMP-reader/materials/test_img/test2.bmp

run_test3:
	./bmp_reader /home/dorothyz/project/c++/BMP-reader/materials/test_img/abc

run_test4:
	./bmp_reader /home/dorothyz/project/c++/BMP-reader/materials/test_img/test4.bmp

run_test5:
	./bmp_reader /home/dorothyz/project/c++/BMP-reader/materials/test_img/test5.bmp

run_test6:
	./bmp_reader /home/dorothyz/project/c++/BMP-reader/materials/test_img/test6.bmp

run_test7:
	./bmp_reader /home/dorothyz/project/c++/BMP-reader/materials/test_img/amogus.bmp

gcov_report:FLAGS += $(GCOV)
gcov_report: clean test
	lcov -t "gcov_report" --no-external -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open ./report/index.html

test: clean
	$(CC) $(FLAGS) bmp_reader.cpp tests/tests.cpp -o TEST $(GTEST_LIB)
	./TEST

clean:
	rm -rf *.out bmp_reader ./*.gcda ./*.gcno TEST ./*.info