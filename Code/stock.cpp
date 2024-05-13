#include "stock.h"

std::vector<cardType> stockType::peel3() //from stock to stockVis
{
    std::vector<cardType> peeledCards;
    for (int i = 0; i < 3; i++)
    {
        if(!isEmpty())
        {
        peeledCards.push_back(stack.top());
        stack.pop();
        }
    }
    return peeledCards;
}


//+ operator to add card to stockType stack
stockType stockType::operator+(const cardType &newCard)
{
    stack.push(newCard);
    return *this;
}
//friend operator for +
stockType operator+(const cardType &newCard, stockType &currentStack)
{
    return currentStack + newCard;
}