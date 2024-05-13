#ifndef RESERVE_H
#define RESERVE_H
#include <vector>
#include <stack>
#include "stack.h"
#include "deck.h"

class reserveType : public stackType
{
public:
    //+ operator to add cart to reserveType
    reserveType operator+(const cardType &newCard);
    friend reserveType operator+(const cardType &newCard, reserveType &currentStack);

protected:
    int counter;
};

#endif