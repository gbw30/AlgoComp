//
// Created by Gabriel Wong Chong on 12/3/2024.
//

#include "City.h"

#include <utility>

City::City(int id, std::string n, std::string st, std::string cn, float lat, float lon, int elev, int pop,
           std::string tz) : cityID(id), name(std::move(n)), state(std::move(st)), country(std::move(cn)), latitude(lat),
                             longitude(lon), elevation(elev), population(pop), timezone(std::move(tz)) {}