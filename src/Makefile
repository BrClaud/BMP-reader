CC = g++
FLAGS = -Wall -Wextra -Werror

all : clean build run_test1

build:
	$(CC) $(FLAGS) -g *.cpp -o bmp_reader

run_test1:
	./bmp_reader /home/dorothyz/project/c++/BMP-reader/materials/test1.bmp

clean:
	rm -rf *.out bmp_reader