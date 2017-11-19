CC=g++

WARN=-Wall -W -Wno-missing-field-initializers -std=c++11
OPT=-O2

CFLAGS=$(WARN) $(OPT)

LIBS=./lib/card.h ./lib/card.cpp ./lib/Maploader.h ./lib/Maploader.cpp ./lib/map.h ./lib/map.cpp ./lib/player.h ./lib/player.cpp ./lib/dice.h ./lib/die.h ./lib/dice.cpp ./lib/die.cpp ./lib/game.h ./lib/game.cpp ./lib/observer.h ./lib/observer.cpp

STD=-std=c++11

all:

# Assignment 3
a3part2: clean
	$(CC) $(STD) $(OPTS) $(LIBS) part2.cpp -o part2

a3part3: clean
	$(CC) $(STD) $(OPTS) $(LIBS) part3.cpp -o part3

# Assignment 2
part1: clean
	$(CC) $(STD) $(OPTS) $(LIBS) part1.cpp -o part1

part2: clean
	$(CC) $(STD) $(OPTS) $(LIBS) part2.cpp -o part2

part3: clean
	$(CC) $(STD)  $(OPTS) $(LIBS) part3.cpp -o part3

part4: clean
	$(CC) $(STD) $(OPTS) $(LIBS) part4.cpp -o part4

part5: clean
	$(CC) $(STD) $(OPTS) $(LIBS) part5.cpp -o part5

part6: clean
	$(CC) $(STD) $(OPTS) $(LIBS) part6.cpp -o part6

# Assignment 1
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
	rm -rf part1 part2 part3 part4 part5 part6


.PHONY: clean all
