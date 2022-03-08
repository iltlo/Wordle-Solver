FLAGS = -pedantic-errors -std=c++11

all: wordle

wordle.o: wordle.cpp wordle.hpp
	g++ $(FLAGS) -c $<

wordle: wordle.o
	g++ $(FLAGS) $< -o $@

clean:
	rm -f *.o wordle

.PHONY: clean