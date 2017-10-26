CC=g++

WARN=-Wall -W -Wno-missing-field-initializers
OPT=-O2

CFLAGS=$(WARN) $(OPT)

all:

part1:

# part 1
	g++ -std=c++11 part1.cpp  ./lib/card.h ./lib/card.cpp ./lib/Maploader.h ./lib/Maploader.cpp ./lib/map.h ./lib/map.cpp ./lib/player.h ./lib/player.cpp ./lib/dice.h ./lib/die.h ./lib/dice.cpp ./lib/die.cpp  -o part1

part2:

# part 2
	g++ -std=c++11 part2.cpp ./lib/player.h ./lib/player.cpp ./lib/dice.h ./lib/die.h ./lib/dice.cpp ./lib/die.cpp  -o part2

# Previous Assignment parts
player: 
	g++ ./lib/card.h ./lib/card.cpp ./lib/dice.h ./lib/dice.cpp ./lib/die.h ./lib/die.cpp ./lib/player.h ./lib/player.cpp ./lib/player_test.cpp -o player_test

maploader:
	g++ ./lib/Maploader.h ./lib/Maploader.cpp ./lib/map.h ./lib/map.cpp ./lib/map_test.cpp -o maploader_test

dice:
	g++ ./lib/die.h ./lib/die.cpp ./lib/dice.h ./lib/dice.cpp ./lib/dice_test.cpp -o dice_test

map:
	g++ ./lib/map.h ./lib/map.cpp ./lib/map_test.cpp -o map_test
cards:
	$(CC) $(CFLAGS) ./lib/card.cpp ./lib/card.h ./lib/card_test.cpp -o card_test
clean:
	rm -rf player.h.gch player_test
	rm -rf Dice.h.gch Die.h.gch dice_test
	rm -rf maploader_test
	rm -rf map_test
	rm -rf card.h.gch card_test
	rm -rf risk
	rm -rf part1
	rm -rf part2