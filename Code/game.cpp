#include "game.h"
#include <iomanip>

// constructor
gameType::gameType()
{
    // exists in private member
}

// sorts deck into stacks
void gameType::dealGame()
{

    // pass deck vector elements into stacks
    //-- 13 in reserve
    for (int i = 0; i < 13; i++)
    {
        reserve = reserve + gameDeck.deck.back();
        gameDeck.deck.pop_back();
    }
    //-- 1 in foundation
    foundation[0] = foundation[0] + gameDeck.deck.back();
    gameDeck.deck.pop_back();
    //-- 1 in each tableau
    for (int j = 0; j < 4; j++)
    {
        tableau[j] = tableau[j] + gameDeck.deck.back();
        gameDeck.deck.pop_back();
    }
    //-- rest in stock (34)
    while (!gameDeck.deck.empty())
    {
        stock = stock + gameDeck.deck.back();
        gameDeck.deck.pop_back();
    }
}

// not for final part of layout, just data checking
void gameType::printLayout()
{

    /// foundations/
    std::cout << std::setfill('-') << std::setw(24) << "-" << std::endl;
    std::cout << ".F1. .F2. .F3. .F4." << std::endl;
    // foundations top
    for (int i = 0; i < 4; i++)
    {
        if (!gameType::foundation[i].isEmpty())
        {
            if (foundation[i].getTopCard() == foundation[i].getBaseCard())
            {
                std::cout << "|--| ";
            }
            else
            {
                std::cout << "|";
                cardType::displayCard(foundation[i].getTopCard());
                std::cout << "| ";
            }
        }
        else
        {
            std::cout << "|--| ";
        }
    }
    std::cout << std::endl;
    // foundations base
    for (int i = 0; i < 4; i++)
    {
        if (!gameType::foundation[i].isEmpty())
        {
            std::cout << "|";
            cardType::displayCard(foundation[i].getBaseCard());
            std::cout << "| ";
        }
        else
        {
            std::cout << "|--| ";
        }
    }

    /// tableaus/
    std::cout << std::endl
              << std::setfill('-') << std::setw(24) << "-" << std::endl
              << ".T1. .T2. .T3. .T4." << std::endl;
    // tableaus base
    for (int i = 0; i < 4; i++)
    {
        if (!gameType::tableau[i].isEmpty())
        {
            std::cout << "|";
            cardType::displayCard(tableau[i].getBaseCard());
            std::cout << "| ";
        }
        else
        {
            std::cout << "|--| ";
        }
    }
    /// reserve/ view
    std::cout << "R:";
    if (!gameType::reserve.isEmpty())
    {
        cardType::displayCard(reserve.getTopCard());
    }
    else
    {
        std::cout << "--";
    }
    std::cout << std::endl;
    // tableaus top
    for (int i = 0; i < 4; i++)
    {
        if (tableau[i].getTopCard() == tableau[i].getBaseCard())
        {
            std::cout << "|--| ";
        }
        else if (!gameType::tableau[i].isEmpty())
        {
            std::cout << "|";
            cardType::displayCard(tableau[i].getTopCard());
            std::cout << "| ";
        }
        else
        {
            std::cout << "|--| ";
        }
    }
    /// stock/ view
    std::cout << std::endl
              << std::setfill('-') << std::setw(24) << "-" << std::endl
              << "S:";
    if (!stock.isEmpty())
    {
        cardType::displayCard(stock.getTopCard());
    }
    else
    {
        std::cout << "--";
    }
    std::cout << "  V:";
    if (!stockVis.isEmpty())
    {
        cardType::displayCard(stockVis.getTopCard());
    }
    else
    {
        std::cout << "--";
    }

    std::cout << std::endl;
}

void gameType::shuffle()
{
    gameDeck.shuffle();
}

void gameType::peel3() // from stock to stockVis
{
    if (stock.isEmpty())
    {
        redeal();
    }
    std::vector<cardType> peeledCards = stock.peel3();
    for (std::vector<cardType>::iterator it = peeledCards.begin(); it != peeledCards.end(); ++it)
    {
        stockVis.push(*it);
    }
}

void gameType::redeal() // redeals stock
{
    stock.swap(stockVis);
}

//"Move a card"
void gameType::moveToptoStack() // stack.top() moves by user picks
{
    while (true)
    {
        int stackChoice = 0;
        int destinationChoice = 0;
        std::cout << "Move card from which stack?" << std::endl
                  << "1. Stock" << std::endl
                  << "2. Reserve" << std::endl
                  << "3. Tableau" << std::endl
                  << "4. Go Back" << std::endl
                  << "--Your entry: ";
        std::cin >> stackChoice;
        while ((stackChoice < 1 || stackChoice > 4) || std::cin.fail())
        {
            std::cout << "**That's not an option, try again: ";
            // Clear the input stream and ignore the invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cin >> stackChoice;
        }
        switch (stackChoice) // FROM
        {
            int pile;
            bool validMove;
        case 1: // FROM stock
            std::cout << "To which stack?" << std::endl
                      << "1. Foundation" << std::endl
                      << "2. Tableau" << std::endl
                      << "3. Go Back" << std::endl
                      << "--Your entry: ";
            std::cin >> destinationChoice;
            while ((destinationChoice < 1 || destinationChoice > 3) || std::cin.fail())
            {
                std::cout << "**That's not an option, try again: ";
                // Clear the input stream and ignore the invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cin >> destinationChoice;
            }

            // check if stock is existing----------------------------------------
            if (stockVis.isEmpty())
            {
                std::cout << "**Stock is empty, try again." << std::endl;
                break;
            }
            // continuing to the piles to move to----------------------------------
            switch (destinationChoice) // TO
            {
            case 1: // TO foundation
                std::cout << "To which foundation pile? (1-4): ";
                std::cin >> pile;
                // data validation for pile
                while ((pile < 1 || pile > 4) || std::cin.fail())
                {
                    std::cout << "**That's not a pile option, try again: ";
                    // Clear the input stream and ignore the invalid input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> pile;
                }
                // check if foundation is empty and compare to found[0] base value
                validMove = foundation[pile - 1].checkIfValidMove(stockVis.getTopCard(), foundation[0]);
                // make sure pile will allow color & value-------------------------
                if (validMove == true)
                {
                    stockVis.move(foundation[pile - 1]);
                    printASCIILayout();
                    break;
                }
                else
                {
                    std::cout << "**Invalid move." << std::endl;
                    break;
                }
            case 2: // TO tableau
                std::cout << "To which tableau pile? (1-4): ";
                std::cin >> pile;
                // data validation for pile
                while ((pile < 1 || pile > 4) || std::cin.fail())
                {
                    std::cout << "**That's not a pile option, try again: ";
                    // Clear the input stream and ignore the invalid input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> pile;
                }
                // check if tableau is existing---------------------------------
                if (tableau[pile - 1].isEmpty())
                {
                    std::cout << "**Invalid move.";
                    break;
                }
                // make sure pile will allow color & value-------------------------
                validMove = tableau[pile - 1].checkIfValidMove(stockVis.getTopCard());
                if (validMove == true)
                {
                    stockVis.move(tableau[pile - 1]);
                    printASCIILayout();
                    break;
                }
                else
                {
                    std::cout << "**Invalid move." << std::endl;
                    break;
                }
            case 3:
                std::cout << std::endl;
                break;
            default:
                std::cout << "**Invalid, try again. (1-3): ";
                break;
            }
            break;
        case 2: // FROM reserve
            std::cout << "To which stack?" << std::endl
                      << "1. Foundation" << std::endl
                      << "2. Tableau" << std::endl
                      << "3. Go Back" << std::endl
                      << "--Your entry: ";
            std::cin >> destinationChoice;
            while ((destinationChoice < 1 || destinationChoice > 3) || std::cin.fail())
            {
                std::cout << "**That's not an option, try again: ";
                // Clear the input stream and ignore the invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cin >> destinationChoice;
            }

            // check if reserve is existing----------------------------------------
            if (reserve.isEmpty())
            {
                std::cout << "*Reserve is empty, try again." << std::endl;
                break;
            }
            // continuing to the piles to move to----------------------------------
            switch (destinationChoice) // TO
            {
            case 1: // TO foundation
                std::cout << "Which foundation pile? (1-4): ";
                std::cin >> pile;
                std::cout << std::endl;
                // data validation for pile
                while ((pile < 1 || pile > 4) || std::cin.fail())
                {
                    std::cout << "**That's not a pile option, try again: ";
                    // Clear the input stream and ignore the invalid input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> pile;
                }
                // I dont think I need this*********************************************************
                //  make sure pile will allow color & value-------------------------
                validMove = foundation[pile - 1].checkIfValidMove(reserve.getTopCard(), foundation[0]);
                if (validMove == true)
                {
                    reserve.move(foundation[pile - 1]);
                    printASCIILayout();
                    break;
                }
                else
                {
                    std::cout << "**Invalid move." << std::endl;
                    break;
                }
            case 2: // TO tableau
                std::cout << "Which tableau pile? (1-4): ";
                std::cin >> pile;
                std::cout << std::endl;
                // data validation for pile
                while ((pile < 1 || pile > 4) || std::cin.fail())
                {
                    std::cout << "**That's not a pile option, try again: ";
                    // Clear the input stream and ignore the invalid input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> pile;
                }
                // check if tableau is existing---------------------------------
                if (tableau[pile - 1].isEmpty())
                {
                    std::cout << "**Tableau is empty, try again." << std::endl;
                    break;
                }
                // make sure pile will allow color & value-------------------------
                validMove = tableau[pile - 1].checkIfValidMove(reserve.getTopCard());
                if (validMove == true)
                {
                    reserve.move(tableau[pile - 1]);
                    printASCIILayout();
                    break;
                }
                else
                {
                    std::cout << "**Invalid move." << std::endl;
                    break;
                }
            case 3:
                break;
            default:
                std::cout << "**Invalid, try again. (1-3): ";
                break;
            }
            break;
        case 3: // FROM Tableau
            int tabNum;
            std::cout << "From which tableau? (1-4): ";
            std::cin >> tabNum;
            // data validation for tableau choice
            while ((tabNum < 1 || tabNum > 4) || std::cin.fail())
            {
                std::cout << "**That's not a tableau number, try again: ";
                // Clear the input stream and ignore the invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> tabNum;
            }

            // if empty, break out because invalid move, otherwise continue
            if (!tableau[tabNum - 1].isEmpty())
            {
                std::cout << std::endl;
                std::cout << "To which stack?" << std::endl
                          << "1. Foundation" << std::endl
                          << "2. Tableau" << std::endl
                          << "3. Go Back" << std::endl
                          << "--Your entry: ";
                std::cin >> destinationChoice;
            }
            else
            {
                std::cout << "**There is no cards in that tableau stack." << std::endl;
                break;
            }

            while ((destinationChoice < 1 || destinationChoice > 3) || std::cin.fail())
            {
                std::cout << "**That's not an option, try again: ";
                // Clear the input stream and ignore the invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cin >> destinationChoice;
            }

            // continuing to the piles to move to----------------------------------
            switch (destinationChoice) // TO
            {
            case 1: // TO foundation
                std::cout << "Which foundation pile? (1-4): ";
                std::cin >> pile;
                std::cout << std::endl;
                // data validation for pile
                while ((pile < 1 || pile > 4) || std::cin.fail())
                {
                    std::cout << "**That's not a pile option, try again: ";
                    // Clear the input stream and ignore the invalid input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> pile;
                }
                validMove = foundation[pile - 1].checkIfValidMove(tableau[tabNum - 1].getTopCard(), foundation[0]);
                if (validMove == true)
                {
                    tableau[tabNum - 1].move(foundation[pile - 1]);
                    printASCIILayout();
                    break;
                }
                else
                {
                    std::cout << "**Invalid move." << std::endl;
                    break;
                }
            case 2: // TO tableau
                std::cout << "Which tableau pile? (1-4): ";
                std::cin >> pile;
                std::cout << std::endl;
                // data validation for pile
                while ((pile < 1 || pile > 4) || std::cin.fail())
                {
                    std::cout << "**That's not a pile option, try again: ";
                    // Clear the input stream and ignore the invalid input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> pile;
                }
                // if trying to move from one tableau to the SAME tableau
                if (tabNum == pile)
                {
                    std::cout << "**This is the same tableau card that is attempting to be moved." << std::endl;
                    break;
                }

                // check if tableau is existing---------------------------------
                if (tableau[pile - 1].isEmpty() && !(reserve.isEmpty()))
                {
                    std::cout << "**There is still reserve cards to fill the tableau, try again." << std::endl;
                    break;
                }
                validMove = tableau[pile - 1].checkIfValidMove(tableau[tabNum - 1].getTopCard());
                if (validMove == true)
                {
                    tableau[tabNum - 1].stackType::move(tableau[pile - 1]);
                    printASCIILayout();
                    break;
                }
                else
                {
                    std::cout << "**Invalid move." << std::endl;
                    break;
                }
            case 3:
                break;
            default:
                std::cout << "**Invalid, try again. (1-3): ";
                break;
            }
            break;
        case 4: // go back
            std::cout << std::endl;
            return; // to be down with loop
        default:
            std::cout << "**Invalid, try again. (1-4): ";
            break;
        }
    }
}

//"Move tableau stack"
void gameType::moveTableauStack()
{
    int sourceNum;
    int destinationNum;

    // source stack input
    std::cout << "Which tableau stack to move? (1-4): ";
    std::cin >> sourceNum;
    while ((sourceNum < 1 || sourceNum > 4) || std::cin.fail())
    {
        std::cout << std::endl;
        std::cout << "**That's not an option, try again: ";
        // Clear the input stream and ignore the invalid input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cin >> sourceNum;
    }
    // check if source stack is empty
    if (tableau[sourceNum - 1].isEmpty())
    {
        std::cout << std::endl;
        std::cout << "**No need, tableau youre trying to move is empty." << std::endl;
        return;
    }

    // destination stack input
    std::cout << "To which tableau stack? (1-4): ";
    std::cin >> destinationNum;
    while ((destinationNum < 1 || destinationNum > 4) || std::cin.fail())
    {
        std::cout << std::endl;
        std::cout << "**That's not an option, try again: ";
        // Clear the input stream and ignore the invalid input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cin >> destinationNum;
    }
    // check if destination stack is empty
    if (tableau[destinationNum - 1].isEmpty())
    {
        std::cout << std::endl;
        std::cout << "**No need, tableau youre trying to move to is empty." << std::endl;
        return;
    }

    // for moving tableau to tableau then check for reserve card
    if (tableau[sourceNum - 1].checkIfTableauStackMoveValid(tableau[sourceNum - 1], tableau[destinationNum - 1]))
    {
        while (!tableau[sourceNum - 1].isEmpty())
        {
            cardType card = tableau[sourceNum - 1].top();
            tableau[sourceNum - 1].pop();
            tableau[destinationNum - 1].push(card);
        }
        if (tableau[sourceNum - 1].isEmpty())
        {
            if (!reserve.isEmpty())
            {
                std::cout << "***Filling empty tableau with reserve card*" << std::endl;
                cardType emptyTableauFillCard = reserve.top();
                reserve.pop();
                tableau[sourceNum - 1].push(emptyTableauFillCard);
            }
        }
    }
    else
    {
        // there is error statments within checkIfTableauStackMoveValid()
        return;
    }
}

// "Reprint layout"
void gameType::printASCIILayout()
{
    std::cout << printFoundationASCIICards();
    std::cout << printTableauASCIICards();
    std::cout << printStockASCIICards();
}

// "Game status" (win or standstill or continue)
bool gameType::checkGameStatus()
{
    if (isWon() == true)
    {
        std::cout << "*****~~You won the game!!~~*****" << std::endl;
        return true;
    }
    else if (isStandstill())
    {
        std::cout << "**Uh oh, there's officially no more moves left."
                  << std::endl
                  << "Game is at a stand still. Rip." << std::endl;
    }
    else
    {
        return false;
    }
    return false;
}

// winner if all foundations complete
bool gameType::isWon()
{
    for (int i = 0; i < 4; i++)
    {
        if (!foundation[i].isComplete())
        {
            return false;
        }
    }
    return true;
}

bool gameType::isStandstill()
{
    int pile;
    bool validMove;
    // FROM stock-------------------------------------
    if (!stockVis.isEmpty() || !stock.isEmpty())
    {
        // copies to not fuck with game
        stockType tempStockVis(stockVis);
        stockType tempStock(stock);
        stockType tempFullStack;
        bool cycledThrough = false;
        while (!tempStock.isEmpty())
        {
            // pop 3
            for (int i = 0; i < 3 && !tempStock.isEmpty(); i++)
            {
                cardType card = tempStock.top();
                tempStock.pop();
                tempStockVis.push(card);
            }

            // check if play is possible
            if (!tempStockVis.isEmpty())
            {
                cardType topCard = tempStockVis.top();

                // to tableau and foundations---------
                for (int i = 0; i < 4; i++)
                {
                    if (tableau[i].checkIfValidMove(topCard))
                    {
                        return false;
                    }
                    if (!foundation[i].isEmpty() && foundation[i].checkIfValidMove(topCard, foundation[i]))
                    {
                        return false;
                    }
                }
            }

            // to refill stack------------------
            if (tempStock.isEmpty())
            {
                // to check if we already checked full stock after putting stockVis back in
                if (cycledThrough == false)
                {
                    while (!tempStockVis.isEmpty())
                    {
                        tempFullStack.push(tempStockVis.top());
                        tempStockVis.pop();
                    }
                    tempStock = tempFullStack;
                    cycledThrough = true;
                }
            }
        }
        // FROM reserve--------------------------------
        if (!reserve.isEmpty())
        {
            // to tableau and foundations---
            cardType reserveTop = reserve.top();
            for (int i = 0; i < 4; i++)
            {
                if (tableau[i].checkIfValidMove(reserveTop))
                {
                    return false;
                }
                if (!foundation[i].isEmpty() && foundation[i].checkIfValidMove(reserveTop, foundation[i]))
                {
                    return false;
                }
            }
        }
        // FROM tableau tops-------------------------
        for (int i = 0; i < 4; i++)
        {
            if (!tableau[i].isEmpty())
            {
                cardType tableauCard = tableau[i].getTopCard();
                // to foundations and tableaus------
                for (int j = 0; j < 4; j++)
                {
                    // if move available
                    if (foundation[j].checkIfValidMove(tableauCard, foundation[j]))
                    {
                        return false;
                    }
                }
                for (int j = 0; j < 4; j++)
                {
                    // if move available
                    if (tableau[j].checkIfValidMove(tableauCard))
                    {
                        return false;
                    }
                }
            }
        }
        // TABLEAU COLUMNS---------------------------
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (tableau[i].checkIfTableauStackMoveValid(tableau[i], tableau[j]))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// parts to print layout
std::string gameType::printFoundationASCIICards()
{
    std::ostringstream out;
    // ┌─────────┐

    for (int i = 0; i < 4; i++)
    {
        out << "  ┌─────────┐ ";
    }
    out << std::endl
        << " ";

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::left;
        out << " │ " << std::setw(8);
        if (!gameType::foundation[i].isEmpty())
        {
            out << gameType::foundation[i].getTopCard().getFaceLabel();
        }
        else
        {
            out << "--";
        }
        out << "│  ";
    }

    out << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::left;
        out << "  │" << std::setw(9) << " "
            << "│ ";
    }

    out << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::right;
        out << "  │";
        if (!gameType::foundation[i].isEmpty())
        {
            out << std::setw(7);
            out << gameType::foundation[i].getTopCard().getSuitLabel();
            // out << suitStr[p[i].p[p[i].topCard].s];
        }
        else
        {
            out << std::setw(5);
            out << " ";
        }
        out << std::setw(4) << " "
            << "│ ";
    }

    out << std::endl;
    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::left;
        out << "  │" << std::setw(9) << " "
            << "│ ";
    }

    out << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::right;
        out << "  │" << std::setw(8);
        if (!gameType::foundation[i].isEmpty())
        {
            out << gameType::foundation[i].getTopCard().getFaceLabel();
        }
        else
        {
            out << " ";
        }
        out << " │ ";
    }

    out << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << "  └─────────┘ ";
    }

    out << std::endl;

    // for bottom bases peakaboos of foundation--------------------------
    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::right;
        if (gameType::foundation[i].size() > 1)
        {
            out << "  │" << std::setw(7);
            out << foundation[i].getBaseCard();
        }
        else
        {
            out << "  │" << std::setw(8);
            out << "--";
        }
        out << " │ ";
    }

    out << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << i + 1 << " └─────────┘ ";
        // out << setw(6) << "'" << "'  ";
    }
    out << std::endl;

    return out.str();
}

std::string gameType::printTableauASCIICards() // with reserve pile
{
    std::ostringstream out;
    // ┌─────────┐

    // for top bases peakaboos of tableau--------------------------
    for (int i = 0; i < 4; i++)
    {
        out << "  ┌─────────┐ ";
        // out << setw(6) << "'" << "'  ";
    }
    out << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::right;
        if (gameType::tableau[i].size() > 1)
        {
            out << "  │" << std::setw(7);
            out << tableau[i].getBaseCard();
        }
        else
        {
            out << "  │" << std::setw(8);
            out << "--";
        }
        out << " │ ";
    }

    out << "  ┌─────────┐ " << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << "  ┌─────────┐ ";
    }

    // reserve card face part--------------
    out << std::setfill(' ') << std::left;
    out << "  │ " << std::setw(8);
    if (!gameType::reserve.isEmpty())
    {
        out << gameType::reserve.getTopCard().getFaceLabel();
    }
    else
    {
        out << "--";
    }
    out << "│ " << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::left;
        out << "  │ " << std::setw(8);
        if (!gameType::tableau[i].isEmpty())
        {
            out << gameType::tableau[i].getTopCard().getFaceLabel();
        }
        else
        {
            out << "--";
        }
        out << "│ ";
    }

    // reserve card fill part-------------
    out << std::setfill(' ') << std::left;
    out << "  │" << std::setw(9) << " "
        << "│ ";
    out << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::left;
        out << "  │" << std::setw(9) << " "
            << "│ ";
    }

    // reserve card suit part------------
    out << std::setfill(' ') << std::right;
    out << "  │" << std::setw(7);
    if (!gameType::reserve.isEmpty())
    {
        out << gameType::reserve.getTopCard().getSuitLabel();
    }
    else
    {
        out << " ";
    }
    out << std::setw(4) << " "
        << "│ " << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::right;
        out << "  │";
        if (!gameType::tableau[i].isEmpty())
        {
            out << std::setw(7);
            out << gameType::tableau[i].getTopCard().getSuitLabel();
        }
        else
        {
            out << std::setw(5);
            out << " ";
        }
        out << std::setw(4) << " "
            << "│ ";
    }

    // reserve card fill part-------------
    out << std::setfill(' ') << std::left;
    out << "  │" << std::setw(9) << " "
        << "│ ";
    out << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::left;
        out << "  │" << std::setw(9) << " "
            << "│ ";
    }

    // reserve card face part------------------
    out << std::setfill(' ') << std::right;
    out << "  │" << std::setw(8);
    if (!gameType::reserve.isEmpty())
    {
        out << gameType::reserve.getTopCard().getFaceLabel();
    }
    else
    {
        out << "--";
    }
    out << " │ " << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << std::setfill(' ') << std::right;
        out << "  │" << std::setw(8);
        if (!gameType::tableau[i].isEmpty())
        {
            out << gameType::tableau[i].getTopCard().getFaceLabel();
        }
        else
        {
            out << "--";
        }
        out << " │ ";
    }

    out << "R └─────────┘ " << std::endl;

    for (int i = 0; i < 4; i++)
    {
        out << i + 1 << " └─────────┘ ";
        // out << setw(6) << "'" << "'  ";
    }
    out << std::endl;

    return out.str();
}

std::string gameType::printStockASCIICards()
{
    std::ostringstream out;
    // line 1
    for (int i = 0; i < 2; i++)
    {
        out << "  ┌─────────┐ ";
    }
    out << std::endl;

    // line 2
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            if (!stock.isEmpty())
            {
                out << "  │░░░░░░░░░│";
            }
            else
            {
                out << std::setfill(' ') << std::left;
                out << "  │ " << std::setw(8) << "--"
                    << "│";
            }
        }

        if (i == 1)
        {
            out << std::setfill(' ') << std::left;
            out << "   │ " << std::setw(8);
            if (!stockVis.isEmpty())
            {
                out << stockVis.getTopCard().getFaceLabel();
            }
            else
            {
                out << "--";
            }
            out << "│  ";
        }
    }
    out << std::endl;

    // line 3
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            if (!stock.isEmpty())
            {
                out << "  │░░░░░░░░░│";
            }
            else
            {
                out << std::setfill(' ') << std::left;
                out << "  │ " << std::setw(8) << "  "
                    << "│";
            }
        }
        if (i == 1)
        {
            out << std::setfill(' ') << std::left;
            out << "   │" << std::setw(9) << " "
                << "│ ";
        }
    }
    out << std::endl;

    // line 4
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            if (!stock.isEmpty())
            {
                out << "  │░░░░░░░░░│";
            }
            else
            {
                out << std::setfill(' ') << std::left;
                out << "  │ " << std::setw(8) << "  "
                    << "│";
            }
        }
        if (i == 1)
        {
            out << std::setfill(' ') << std::right;
            out << "   │";
            if (!stockVis.isEmpty())
            {
                out << std::setw(7);
                out << stockVis.getTopCard().getSuitLabel();
            }
            else
            {
                out << std::setw(5);
                out << " ";
            }
            out << std::setw(4) << " "
                << "│ ";
        }
    }
    out << std::endl;

    // line 5
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            if (!stock.isEmpty())
            {
                out << "  │░░░░░░░░░│";
            }
            else
            {
                out << std::setfill(' ') << std::left;
                out << "  │ " << std::setw(8) << "  "
                    << "│";
            }
        }
        if (i == 1)
        {
            out << std::setfill(' ') << std::left;
            out << "   │" << std::setw(9) << " "
                << "│ ";
        }
    }
    out << std::endl;

    // line 6
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            if (!stock.isEmpty())
            {
                out << "  │░░░░░░░░░│";
            }
            else
            {
                out << std::setfill(' ') << std::right;
                out << "  │ " << std::setw(7) << "--"
                    << " │";
            }
        }
        if (i == 1)
        {
            out << std::setfill(' ') << std::right;
            out << "   │" << std::setw(8);
            if (!stockVis.isEmpty())
            {
                out << stockVis.getTopCard().getFaceLabel();
            }
            else
            {
                out << "--";
            }
            out << " │ ";
        }
    }
    out << std::endl;

    out << "  └─────────┘  S└─────────┘";
    out << std::endl;

    return out.str();
}

// reference from Angela-------------------
/*
std::string gameType::printStockASCIICard()
{
    std::ostringstream out;
    if (!gameType::stock.isEmpty())
    {
        out << "┌─────────┐ " << std::endl;
        out << std::setfill(' ') << std::left;
        out << "│ " << std::setw(8);
        out << gameType::stock.getTopCard().getFace();
        out << "│  " << std::endl;
        out << std::setfill(' ') << std::left;
        out << "│" << std::setw(9) << " "
            << "│ " << std::endl;
        out << std::setfill(' ') << std::right;
        out << "│" << std::setw(7);
        out << gameType::stock.getTopCard().getSuit();
        out << std::setw(4) << " "
            << "│ " << std::endl;
        out << std::setfill(' ') << std::left;
        out << "│" << std::setw(9) << " "
            << "│ " << std::endl;
        out << std::setfill(' ') << std::right;
        out << "│" << std::setw(8);
        out << gameType::stock.getTopCard().getFace();
        out << " │ " << std::endl;
        out << "└─────────┘ " << std::endl;
    }
    else
    {
        out << "┌─────────┐" << std::endl;  //
        out << "│░░░░░░░░░│" << std::endl;
        out << "│░░░░░░░░░│" << std::endl;
        out << "│░░░░░░░░░│" << std::endl;
        out << "│░░░░░░░░░│" << std::endl;
        out << "│░░░░░░░░░│" << std::endl;
        out << "└─────────┘" << std::endl;
    }
    return out.str();
}

std::string gameType::printReserveASCIICard()
{
    std::ostringstream out;
    if (!gameType::reserve.isEmpty())
    {
        out << "┌─────────┐ " << std::endl;
        out << std::setfill(' ') << std::left;
        out << "│ " << std::setw(8);
        out << gameType::reserve.getTopCard().getFace();
        out << "│  " << std::endl;
        out << std::setfill(' ') << std::left;
        out << "│" << std::setw(9) << " "
            << "│ " << std::endl;
        out << std::setfill(' ') << std::right;
        out << "│" << std::setw(7);
        out << gameType::reserve.getTopCard().getSuit();
        out << std::setw(4) << " "
            << "│ " << std::endl;
        out << std::setfill(' ') << std::left;
        out << "│" << std::setw(9) << " "
            << "│ " << std::endl;
        out << std::setfill(' ') << std::right;
        out << "│" << std::setw(8);
        out << gameType::reserve.getTopCard().getFace();
        out << " │ " << std::endl;
        out << "└─────────┘ " << std::endl;
    }
    else
    {
        out << "┌─────────┐" << std::endl;
        out << "│░░░░░░░░░│" << std::endl;
        out << "│░░░░░░░░░│" << std::endl;
        out << "│░░░░░░░░░│" << std::endl;
        out << "│░░░░░░░░░│" << std::endl;
        out << "│░░░░░░░░░│" << std::endl;
        out << "└─────────┘" << std::endl;
    }
    return out.str();
}
*/