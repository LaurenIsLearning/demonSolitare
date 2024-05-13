#include "card.h"


/*constructor*/
cardType::cardType()
{
}

//constructor
cardType::cardType(faceType face, suitType suit)
{
    this->face = face;
    this->suit = suit;
}

/*setters*/
void cardType::setFace(faceType face)
{
    this->face = face;
}
void cardType::setSuit(suitType suit)
{
    this->suit = suit;
}

/*getters*/
//bc map is CONST, don't use []
std::string cardType::getSuitLabel()
{
    return suitTypeToStr.at(suit);
}
std::string cardType::getFaceLabel()
{
    return faceTypeToStr.at(face);
}

suitType cardType::getSuit() const
{
    return suit;
}

faceType cardType::getFace() const
{
    return face;
}

//display full card ex. A♥
void cardType::displayCard(cardType card)
{
    std::cout << card.getFaceLabel() << card.getSuitLabel();
}

//== cardType and cardType
bool cardType::operator==(const cardType &other)
{
    return (suit == other.suit && face == other.face);
}

//!= for cardType and cardType ((== already exists above))
bool cardType::operator!=(const cardType &other)
{
    return!(*this == other);
}

std::ostream& operator<<(std::ostream &os, const cardType &card)
{
    os << card.faceTypeToStr.at(card.face) << card.suitTypeToStr.at(card.suit);
    return os;
}

const std::map<faceType, std::string> cardType::faceTypeToStr = {
    { ACE, "A" },
    { TWO, "2" },
    { THREE, "3" },
    { FOUR, "4" },
    { FIVE, "5" },
    { SIX, "6" },
    { SEVEN, "7" },
    { EIGHT, "8" },
    { NINE, "9" },
    { TEN, "10" },
    { JACK, "J" },
    { QUEEN, "Q" },
    { KING, "K" }};

const std::map<suitType, std::string> cardType::suitTypeToStr = {
    { DIAMONDS, "♦" },
    { CLUBS, "♣" },
    { HEARTS, "♥" },
    { SPADES, "♠" }};