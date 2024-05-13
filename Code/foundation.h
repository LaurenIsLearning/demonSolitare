#ifndef FOUNDATION_H
#define FOUNDATION_H
#include "stack.h"
#include "deck.h"
#include <vector>
#include <stack>

class foundationType : public stackType
{
public:
    // functions
    //checking if a card can be used on foundation
    bool checkIfValidMove(const cardType&, const foundationType&);
    bool isComplete();

    //+ operator to add cart to foundationType
    foundationType operator+(const cardType &newCard);
    friend foundationType operator+(const cardType &newCard, foundationType &currentStack);

protected:
};

#endif