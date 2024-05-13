#ifndef GAME_H
#define GAME_H
#include "deck.h"
#include "card.h"
#include "stack.h"
#include "stock.h"
#include "reserve.h"
#include "tableau.h"
#include "foundation.h"
#include <vector>
#include <iomanip>
#include <string>
#include <iostream>


class gameType
{
public:
    // constructor
    gameType();
    void dealGame();
    void playGame();
    void printLayout();
    void shuffle();
    void peel3();
    void redeal();
    
    //functions from user choices
    void moveToptoStack();
    void moveTableauStack();
    void printASCIILayout();
    bool checkGameStatus();

    // to determine end of game
    bool isWon();
    bool isStandstill();

    // parts of layout
    std::string printFoundationASCIICards();
    std::string printTableauASCIICards();
    std::string printStockASCIICards();

protected:
    // deck
    deckType gameDeck;
    // stacks
    tableauType tableau[4];
    foundationType foundation[4];
    reserveType reserve;
    stockType stock;
    stockType stockVis;
};

#endif