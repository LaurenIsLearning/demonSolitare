#include "reserve.h"

//+ operator to add card to reserveType stack
reserveType reserveType::operator+(const cardType &newCard)
{
    stack.push(newCard);
    return *this;
}
// friend operator for +
reserveType operator+(const cardType &newCard, reserveType &currentStack)
{
    return currentStack + newCard;
}