/* Program name: main.cpp
 * Author: Lauren Robison
 * Date last updated: 5/12/2023
 * Purpose: Play the game of Canfield (nicknamed DEMON)
 */

#include "game.h"
#include "deck.h"
#include "stack.h"
#include <iostream>
#include <iomanip>

int main()
{
// to have suit symbols work
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // create deck
    gameType game;

    /*// print deck
    deck.printDeck();
    std::cout << std::endl;*/

    // shuffle deck
    game.shuffle();
    game.dealGame();

    // game beginning
    std::cout << "****************Welcome to DEMON!****************" << std::endl
              << "-------Game beginning.." << std::endl;
    game.printASCIILayout();

    bool playAgain = true;
    // start user choices
    while (playAgain == true)
    {
        while (true)
        {
            int userChoice;
            std::cout << "1. Peel 3 cards" << std::endl
                      << "2. Move a card" << std::endl
                      << "3. Move tableau stack" << std::endl
                      << "4. Reprint layout" << std::endl
                      << "5. Game status" << std::endl
                      << "6. Quit" << std::endl
                      << "--Your entry: ";
            std::cin >> userChoice;

            // to data validate
            while ((!(userChoice >= 1 && userChoice <= 6)) || std::cin.fail())
            {
                std::cout << "**Not recognized, try again: ";
                // Clear the input stream and ignore the invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> userChoice;
            }
            switch (userChoice)
            {
            case 1: // for "Peel 3 cards"
                game.peel3();
                game.printASCIILayout();
                // printLayout(); //-------can delete this**********
                break; // for "Move a card"
            case 2:
                game.moveToptoStack();
                break;
            case 3: // for "Move tableau stack"
                game.moveTableauStack();
                break;
            case 4: // for "Reprint layout"
                std::cout << "Reprinting.........." << std::endl;
                game.printASCIILayout();
                break;
            case 5: // for "Game status"
                if (game.checkGameStatus() == true)
                {
                    int playOrNah;
                    std::cout << "Do you want to play again?" << std::endl
                              << "1. Heck naw." << std::endl
                              << "2. Duh, yes please." << std::endl;
                    std::cin >> playOrNah;
                    while ((playOrNah < 1 || playOrNah > 2) || std::cin.fail())
                    {
                        std::cout << "**That's not an option, try again: ";
                        // Clear the input stream and ignore the invalid input
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        std::cin >> playOrNah;
                    }
                    std::cout << std::endl;
                    if (playOrNah == 1)
                    {
                        playAgain = false;
                    }
                }
                else
                {
                    std::cout << std::endl;
                    std::cout << "**There is still moves left to be made!" << std::endl;
                }
                break;
            case 6: // for "Quit"
                std::cout << "Bye!" << std::endl;
                playAgain = false;
                break;
            }

            // end game
            if (playAgain == false)
            {
                break;
            }
        }
        // play again ---------------------
        if (playAgain)
        {
            // shuffle deck and deal game again
            game.shuffle();
            game.dealGame();

            std::cout << "****************Welcome to DEMON!****************" << std::endl
                      << "-------Game beginning.." << std::endl;
            game.printASCIILayout();
        }
    }

    return 0;
}