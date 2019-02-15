#ifndef GAMERULES_HH
#define GAMERULES_HH
#include <string>

namespace GameRules {

    // Tarkistaa että pienempi
    bool checkCard(std::string bottom, std::string top);

    // Tarkistaa että kortti on erivärinen
    bool checkSuit(std::string bottom, std::string top);

    // Tarkastaa että kortti on samaa maata ja yhden numeron suurempi
    bool checkSuitSlot(std::string bottom, std::string top);
}

#endif // GAMERULES_HH
