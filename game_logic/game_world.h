#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "game_class.h"
#include <vector>
#include <string>

class GameWorld {
public:
    // Countries in the game world.
    Country tang;
    Country tujue;
    Country tubo;

    // Constructor initializes the world.
    GameWorld();

    // Display details of all countries.
    void showWorldDetails() const;

    // Destructor to clean up dynamic memory.
    ~GameWorld();

private:
    // Vectors to hold pointers to dynamically allocated cities.
    std::vector<City*> tangCities;
    std::vector<City*> tujueCities;
    std::vector<City*> tuboCities;
};

#endif // GAME_WORLD_H
