#ifndef CARD_H
#define CARD_H
#include <vector>
#include <string>
#include <map>
#include <iostream>

// the following three lines set up the library for the suit symbols
#ifdef _WIN32
#include <Windows.h>
#endif
// clubs (♣), diamonds (♦), hearts (♥), and spades (♠)

// card info enums
enum suitType
{
    DIAMONDS, //[0] Red
    CLUBS,    // 1 Black
    HEARTS,   // 2 Red
    SPADES    // 3 Black
};
enum faceType
{
    ACE, //[0]
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX, // 5
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK, // 10
    QUEEN,
    KING // 12
};

class cardType
{
public:
    // constructor
    cardType();
    cardType(faceType, suitType);
    //setters
    void setFace(faceType);
    void setSuit(suitType);
    // getters
    std::string getSuitLabel();
    std::string getFaceLabel();
    suitType getSuit() const;
    faceType getFace() const;
    // functions
    static void displayCard(cardType); //static bc cardType::
    // maps
    static const std::map<faceType, std::string> faceTypeToStr;
    static const std::map<suitType, std::string> suitTypeToStr;
    
    //overload operators
    bool operator==(const cardType &other);
    bool operator!=(const cardType&);
    //friend operators
    friend std::ostream& operator<<(std::ostream &, const cardType &);

protected:
    faceType face;
    suitType suit;
};

#endif