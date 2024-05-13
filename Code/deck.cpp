#include "deck.h"

/*constructor to initialize full deck*/
deckType::deckType()
{
    // using map as iterator ((why not use ENUMS?)****)
    // suit iterator (sIter)
    for (std::map<suitType, std::string>::const_iterator sIter =
             cardType::suitTypeToStr.begin();
         sIter != cardType::suitTypeToStr.end(); ++sIter)
    {
        // face iterator (fIter)
        for (std::map<faceType, std::string>::const_iterator fIter =
                 cardType::faceTypeToStr.begin();
             fIter != cardType::faceTypeToStr.end(); ++fIter)
        {
            cardType card(fIter->first, sIter->first);
            deck.push_back(card);
        }
    }
}

void deckType::printDeck()
{
    int counter = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            cardType::displayCard(deck[counter]);
            ++counter;
        }
        std::cout << std::endl;
    }
}

/*shuffle cards with user seed input*/
void deckType::shuffle()
{
    // std::random_shuffle(deck.begin(), deck.end());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(deck.begin(), deck.end(), gen);
}
