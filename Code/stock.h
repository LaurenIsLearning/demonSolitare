#ifndef STOCK_H
#define STOCK_H
#include <vector>
#include <stack>
#include "stack.h"
#include "deck.h"

class stockType : public stackType
{
public:
    // functions
    std::vector<cardType> peel3();
    void redeal();

    //+ operator to add cart to stockType
    stockType operator+(const cardType &newCard);
    friend stockType operator+(const cardType &newCard, stockType &currentStack);

protected:
    int counter;
};

#endif