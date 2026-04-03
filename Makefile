build:
	mkdir -p bin/
	mkdir -p object/
	echo "Building cnake"
	echo "Creating object files"
	cc -c src/utils.c -o object/utils.o
	cc -c src/game.c -o object/game.o
	cc src/main.c object/utils.o object/game.o -o bin/cnake -lncurses
	echo "Cnake generated into bin/cnake"
	echo "Cleaning object files"
	rm -rf object

clean:
	rm -f bin/cnake
