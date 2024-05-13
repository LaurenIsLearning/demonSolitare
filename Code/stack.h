#ifndef STACK_H
#define STACK_H
#include "card.h"
#include <vector>
#include <stack>

// stack class info in link:
// https://cplusplus.com/reference/stack/stack/

class stackType
{
public:
    // constructor
    stackType();

    // functions
    bool isEmpty();
    cardType getTopCard() const;
    cardType getBaseCard() const;
    // const cardType &getTopCard() const;
    // const cardType &getBaseCard() const;
    int size();
    void push(const cardType &);
    void swap(stackType &);
    void move(stackType &);
    cardType top();
    cardType pop();

    // for children to use
    virtual bool checkIfValidMove(cardType &);

    //+ operator to add cardType to stackType
    stackType operator+(const cardType &newCard);
    friend stackType operator+(const cardType &newCard, stackType &currentStack);
    //= operator to stackType = stackType
    stackType operator=(const stackType &otherStack);

protected:
    std::stack<cardType> stack;
};

#endif