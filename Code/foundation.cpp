#include "foundation.h"

bool foundationType::checkIfValidMove(const cardType &card, const foundationType &compareToFoundation)
{
    if (isComplete())
    {
        return false;
    }
    if (isEmpty())
    {
        if (card.getFace() == compareToFoundation.getBaseCard().getFace())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // to check if card is the same as foundation base
    if (card.getSuit() != getBaseCard().getSuit())
    {
        return false;
    }
    // to check if card is also the next ascending card
    // stack is circular for foundation so K -> A
    if ((getTopCard().getFace() == ACE && card.getFace() == KING) || (card.getFace() - getTopCard().getFace() == 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// if foundation has 13 cards ((aka full suit))
bool foundationType::isComplete()
{
    return (size() == 13);
}

//+ operator to add card to foundationType stack
foundationType foundationType::operator+(const cardType &newCard)
{
    stack.push(newCard);
    return *this;
}
// friend operator for +
foundationType operator+(const cardType &newCard, foundationType &currentStack)
{
    return currentStack + newCard;
}
