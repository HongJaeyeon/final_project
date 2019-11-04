pushbox:team.o
	g++ -W -Wall -o pushbox team.o -lncurses

team.o:team.cpp
	g++ -W -Wall -c -o team.o team.cpp -lncurses
