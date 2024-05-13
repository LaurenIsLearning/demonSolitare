#include "stack.h"
#include <vector>

// constructor
stackType::stackType()
{
}

// to see if stack is empty
bool stackType::isEmpty()
{
    if (stack.empty())
        return true;
    else
        return false;
}

// functions
//get cards
cardType stackType::getTopCard() const
{
    cardType topCard = stack.top();
    return topCard;
}
cardType stackType::getBaseCard() const
{
    // makes a copy of OG stack
    std::stack<cardType> copyStack(stack);

    while (copyStack.size() > 1)
    {
        copyStack.pop();
    }
    cardType baseCard = copyStack.top();
    return baseCard;
}

/* //get card pointers
const cardType &stackType::getTopCard() const
{
    cardType topCard = stack.top();
    return topCard;
}
const cardType &stackType::getBaseCard() const
{
    // makes a copy of OG stack
    std::stack<cardType> copyStack(stack);

    while (copyStack.size() > 1)
    {
        copyStack.pop();
    }
    cardType baseCard = copyStack.top();
    return baseCard;
} */

int stackType::size()
{
    return stack.size();
}

void stackType::push(const cardType &card)
{
    stack.push(card);
}

void stackType::swap(stackType &other)
{
    std::stack<cardType> temp = stack;
    stack = other.stack;
    other.stack = temp;
}

void stackType::move(stackType &destinationStack)
{
    if (!isEmpty())
    {
        cardType movingCard = stack.top();
        stack.pop();
        destinationStack.push(movingCard);
    }
    else
    {
        std::cout << "**There's no card in this stack to move.";
    }
}

cardType stackType::top()
{
    return stack.top();
}
cardType stackType::pop()
{
    cardType topCard = stack.top();
    stack.pop();
    return topCard;
}

bool stackType::checkIfValidMove(cardType &)
{
    return false;
}

//+ operator to add cardType to stackType
stackType stackType::operator+(const cardType &newCard)
{
    stack.push(newCard);
    return *this;
}
// friend operator for +
stackType operator+(const cardType &newCard, stackType &currentStack)
{
    return currentStack + newCard;
}

//= operator to stackType = stackType
stackType stackType::operator=(const stackType &otherStack)
{
    stack = otherStack.stack;
    return *this;
}