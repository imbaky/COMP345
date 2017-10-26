all:
	g++ -std=c++11 risk.cpp  ./lib/Maploader.h ./lib/Maploader.cpp ./lib/map.h ./lib/map.cpp ./lib/player.h ./lib/player.cpp ./lib/dice.h ./lib/die.h ./lib/dice.cpp ./lib/die.cpp  -o risk