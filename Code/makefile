all: game deck card stack stock reserve tableau foundation main.cpp
	g++ -pedantic-errors -g main.cpp game deck card stack stock reserve tableau foundation -o main
game: game.h game.cpp
	g++ -pedantic-errors -g -c game.cpp -o game
deck: deck.h deck.cpp
	g++ -pedantic-errors -g -c deck.cpp -o deck
card: card.h card.cpp
	g++ -pedantic-errors -g -c card.cpp -o card
stack: stack.h stack.cpp
	g++ -pedantic-errors -g -c stack.cpp -o stack
stock: stock.h stock.cpp
	g++ -pedantic-errors -g -c stock.cpp -o stock
reserve: reserve.h reserve.cpp
	g++ -pedantic-errors -g -c reserve.cpp -o reserve
tableau: tableau.h tableau.cpp
	g++ -pedantic-errors -g -c tableau.cpp -o tableau
foundation: foundation.h foundation.cpp
	g++ -pedantic-errors -g -c foundation.cpp -o foundation
