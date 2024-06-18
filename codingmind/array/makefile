c11 = -std=c++11

all:search removeElement sortedSquares minSubArrayLen generateMatrix

search:search.cpp
	g++ -o search search.cpp

removeElement:removeElement.cpp head.h
	g++ -o removeElement removeElement.cpp

sortedSquares:sortedSquares.cpp head.h
	g++ $(c11) -o sortedSquares sortedSquares.cpp -g 

minSubArrayLen:minSubArrayLen.cpp
	g++ $(c11) -o minSubArrayLen minSubArrayLen.cpp -g

generateMatrix:generateMatrix.cpp
	g++ $(c11) -o generateMatrix generateMatrix.cpp -g
clean:
	rm -rf search removeElement minSubArrayLen sortedSquares generateMatrix

