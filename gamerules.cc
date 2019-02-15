#include "gamerules.hh"
#include "card.hh"

// Funktio saa parametrinaan alla olevan kortin ja päälle tulevan kortin
// tiedot merkkijonomuodossa.
bool GameRules::checkCard(std::string bottom, std::string top)
{
    // Jos slottti on tyhjä
    if(bottom.empty())
        return true;

    // Tarkistaa korttien maat
    if(not checkSuit(bottom, top))
        return false;

    int topValue = stoi(top.substr(0,top.find_first_of(",")));
    int bottomValue = stoi(bottom.substr(0,bottom.find_first_of(",")));

    // Jos lisättävä kortti on pienempi
    if(topValue < bottomValue)
        return true;
    else
        return false;
}

// Funktio saa parametrinaan alla olevan kortin ja päälle tulevan kortin
// tiedot merkkijonomuodossa.
bool GameRules::checkSuit(std::string bottom, std::string top)
{
    // Jos slotissa on tyhjä
    if(bottom.empty())
        return true;

    int topSuit = stoi(top.substr(top.find_first_of(",")+1,1));
    int bottomSuit = stoi(bottom.substr(bottom.find_first_of(",")+1,1));

    // Jos korteilla on sama maa
    if(topSuit == bottomSuit)
        return false;

    // Jos korteilla on sama väri
    else if((topSuit == HEART && bottomSuit == DIAMOND) ||
            (topSuit == DIAMOND && bottomSuit == HEART))
        return false;

    else if((topSuit == CLUB && bottomSuit == SPADE) ||
            (topSuit == SPADE && bottomSuit == CLUB))
        return false;

    else
        return true;
}

// Funktio saa parametrinaan alla olevan kortin ja päälle tulevan kortin
// tiedot merkkijonomuodossa.
bool GameRules::checkSuitSlot(std::string bottom, std::string top)
{
    int topSuit = stoi(top.substr(top.find_first_of(",")+1,1));
    int topValue = stoi(top.substr(0,top.find_first_of(",")));

    // Jos tyhjään suitSlottiin yritetään lisätä jokin muu kuin ykkönen
    if(bottom.empty())
    {
        if(topValue == 1)
            return true;
        else
            return false;
    }

    int bottomSuit = stoi(bottom.substr(bottom.find_first_of(",")+1,1));
    int bottomValue = stoi(bottom.substr(0,bottom.find_first_of(",")));

    // Jos kortit erimaata
    if(topSuit != bottomSuit)
        return false;

    // Jos kortti on yhden suurempi kuin alempi
    if(topValue == bottomValue + 1)
        return true;
    else
        return false;
}
