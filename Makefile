build:
	mkdir -p bin/
	mkdir -p object/
	echo "Building cnake"
	echo "Creating object files"
	cc -c src/utils.c -o object/utils.o
	cc -c src/game.c -o object/game.o
	cc -c src/snake.c -o object/snake.o
	cc src/main.c object/utils.o object/game.o object/snake.o -o bin/cnake -lncurses -std=c99 -Wall -Werror -pedantic
	echo "Cnake generated into bin/cnake"
	echo "Cleaning object files"
	rm -rf object

clean:
	rm -f bin/cnake
