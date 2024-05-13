#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

class deckType
{
public:
    //constructor
    deckType(); //create card and push into vector
    
    //functions
    void printDeck();
    void shuffle();

    //vector for deck
    std::vector<cardType> deck;

protected:

};

#endif