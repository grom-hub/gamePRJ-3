start: test
	./test

test: main.cpp
	g++ -o test main.cpp units.cpp walls.cpp -lncurses -std=c++11

clean:
	rm test
