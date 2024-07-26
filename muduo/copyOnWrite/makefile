all:main

main:main.cpp copyOnWrite.cpp MyDB.cpp
	g++ -std=c++17 -o main main.cpp copyOnWrite.cpp MyDB.cpp `mysql_config --cflags --libs`

clean:
	rm -rf main