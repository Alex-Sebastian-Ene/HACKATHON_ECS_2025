#include "game_world.h"
#include <iostream>

GameWorld::GameWorld()
    : tang("Tang Dynasty", Leader("Taizong of Tang", 50, 40, 100)),
      tujue("Tujue", Leader("Tujue Chieftain", 30, 25, 70)),
      tubo("Tu'bo", Leader("Tu'bo Chieftain", 30, 25, 70))
{
    // --- Tang Dynasty Cities ---
    // Major cities: Shanzhou and Chang'an
    City* shanzhou = new City("Shanzhou");
    shanzhou->population = 200000;
    shanzhou->army_size  = 50000;
    tangCities.push_back(shanzhou);

    City* changan = new City("Chang'an");
    changan->population = 200000;
    changan->army_size  = 50000;
    tangCities.push_back(changan);

    // Other cities: Blanzhou (here given as a large city), Shule, Tingzhiou, Yizhou, Guangzhou.
    City* blanzhou = new City("Blanzhou");
    blanzhou->population = 300000;
    blanzhou->army_size  = 60000;
    tangCities.push_back(blanzhou);

    City* shule = new City("Shule");
    shule->population = 150000;
    shule->army_size  = 30000;
    tangCities.push_back(shule);

    City* tingzhiou = new City("Tingzhiou");
    tingzhiou->population = 150000;
    tingzhiou->army_size  = 30000;
    tangCities.push_back(tingzhiou);

    City* yizhou = new City("Yizhou");
    yizhou->population = 150000;
    yizhou->army_size  = 30000;
    tangCities.push_back(yizhou);

    City* guangzhou = new City("Guangzhou");
    guangzhou->population = 150000;
    guangzhou->army_size  = 30000;
    tangCities.push_back(guangzhou);

    // Add Tang cities to the Tang country.
    for (City* city : tangCities)
        tang.addCity(city);

    // --- Enemy Countries ---
    // Tujue with a placeholder city.
    City* tujueCity = new City("Unknown City T1");
    tujueCity->population = 100000;
    tujueCity->army_size  = 25000;
    tujueCities.push_back(tujueCity);
    tujue.addCity(tujueCity);

    // Tu'bo with a placeholder city.
    City* tuboCity = new City("Unknown City T2");
    tuboCity->population = 100000;
    tuboCity->army_size  = 25000;
    tuboCities.push_back(tuboCity);
    tubo.addCity(tuboCity);
}


GameWorld::~GameWorld() {
    // Clean up the dynamically allocated cities.
    for (City* city : tangCities)
        delete city;
    for (City* city : tujueCities)
        delete city;
    for (City* city : tuboCities)
        delete city;
}
