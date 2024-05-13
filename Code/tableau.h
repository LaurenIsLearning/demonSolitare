#ifndef TABLEAU_H
#define TABLEAU_H
#include <vector>
#include "stack.h"
#include "deck.h"

class tableauType : public stackType
{
public:
    //functions
    //checking if a card can be used on tableau
    bool checkIfValidMove(const cardType &);
    bool checkIfTableauStackMoveValid(tableauType &, tableauType &);

    //+ operator to add card to tableauType
    tableauType operator+(const cardType &newCard);
    friend tableauType operator+(const cardType &newCard, tableauType &currentStack);
    //= operator to tableauType = tableauType
    bool operator==(const tableauType &);


protected:
};

#endif