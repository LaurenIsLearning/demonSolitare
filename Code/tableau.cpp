#include "tableau.h"

// compares card to tableau color and value
bool tableauType::checkIfValidMove(const cardType &card)
{
    // set up colors to compare
    suitType topColor = getTopCard().getSuit();
    // DIAMONDS & HEARTS = red
    // CLUBS & SPADES = black
    suitType cardColor;
    if ((topColor == DIAMONDS || topColor == HEARTS) && (card.getSuit() == DIAMONDS || card.getSuit() == HEARTS))
    {
        return false; //both red
    }
    if ((topColor == CLUBS || topColor == SPADES) && (card.getSuit() == CLUBS || card.getSuit() == SPADES))
    {
        return false; //both black
    }

    // then to check if value is descending by one
    //freakin 2 - ACE = 1 lol
    if ((getTopCard().getFace() - card.getFace() == 1)  || (card.getFace() == ACE && getTopCard().getFace() == TWO))
    {
        return true;
    }
    else
    {

        return false;
    }
    return true;
}

bool tableauType::checkIfTableauStackMoveValid(tableauType &source, tableauType &destination)
{
    if (source == destination)
    {
        return false;
    }

    if (!source.isEmpty() && !destination.isEmpty())
    {
        // make copies so no segmentation errrorrr aaaa
        cardType sourceBaseCard = source.getBaseCard();
        cardType destinationTopCard = destination.getTopCard();

        // use valid card function above to compare
        if (!destination.checkIfValidMove(sourceBaseCard))
        {
            std::cout << std::endl;
            return false;
        }
    }

    return true;
}

//+ operator to add card to tableauType stack
tableauType tableauType::operator+(const cardType &newCard)
{
    stack.push(newCard);
    return *this;
}
// friend operator for +
tableauType operator+(const cardType &newCard, tableauType &currentStack)
{
    return currentStack + newCard;
}

// to compare tableau stacks ==
bool tableauType::operator==(const tableauType &otherTableau)
{
    // if not same size
    if (stack.size() != otherTableau.stack.size())
    {
        return false;
    }
    // copies to be able to compare
    std::stack<cardType> sourceStack = stack;
    std::stack<cardType> destinationStack = otherTableau.stack;

    // to loop through whole stack
    while (!sourceStack.empty())
    {
        if (sourceStack.top() != destinationStack.top())
        {
            return false;
        }
        sourceStack.pop();
        destinationStack.pop();
    }

    return true;
}