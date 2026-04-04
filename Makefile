build:
	mkdir -p bin/
	mkdir -p object/
	echo "Building cnake"
	echo "Creating object files"
	cc -c src/utils.c -o object/utils.o
	cc -c src/game.c -o object/game.o
	cc -c src/snake.c -o object/snake.o
	cc -c src/food.c -o object/food.o
	echo "Object files created"
	cc src/main.c object/utils.o object/game.o object/snake.o object/food.o -o bin/cnake -lncurses -std=c99 -Wall -Werror -pedantic
	echo "Cnake generated into bin/cnake"
	echo "Cleaning object files"
	rm -rf object


optimized:
	mkdir -p bin/
	mkdir -p object/
	echo "Building optimized cnake (-O3)"
	echo "Creating object files"
	cc -c src/utils.c -O3 -o object/utils.o
	cc -c src/game.c -O3 -o object/game.o
	cc -c src/snake.c -O3 -o object/snake.o
	cc -c src/food.c -O3 -o object/food.o
	echo "Object files created"
	cc src/main.c object/utils.o object/game.o object/snake.o object/food.o -O3 -o bin/cnake -lncurses -std=c99 -Wall -Werror -pedantic
	echo "Optimized Cnake generated into bin/cnake"
	echo "Cleaning object files"
	rm -rf object

clean:
	rm -f bin/cnake
