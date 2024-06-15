c11 = -std=c++11

all:fib differentPath

fib:fib.cpp head.h
	g++ $(c11) -o fib head.h fib.cpp

differentPath:differentPath.cpp
	g++ $(c11) -o differentPath head.h differentPath.cpp

clean:
	rm -f fib differentPath